#include "WadFile.hpp"

#include <fstream>

#include "ByteReader.hpp"
#include "WadDirectory.hpp"

std::expected<std::unique_ptr<WadFile>, WadError> WadFile::open(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file) return std::unexpected(WadError::FileNotFound);

    // Recover the file size
    const std::streamoff fileSize = file.tellg();
    if (fileSize < 0) return std::unexpected(WadError::IoError);
    if (fileSize < 12) return std::unexpected(WadError::TooSmall);
    file.seekg(0);

    std::unique_ptr<WadFile> wad(new WadFile());
    wad->m_data.resize(fileSize);

    // Copy data of the file into an array of bytes
    if (!file.read(reinterpret_cast<char*>(wad->m_data.data()), static_cast<std::streamsize>(wad->m_data.size())))
        return std::unexpected(WadError::IoError);

    // Check the type of the file (must be IWAD or PWAD)
    std::string_view type(reinterpret_cast<const char*>(wad->m_data.data()), 4);
    if (type != "IWAD" && type != "PWAD") return std::unexpected(WadError::BadMagic);

    wad->m_nbLumps = readU32(wad->m_data, 4);
    wad->m_infoTableOfs = readU32(wad->m_data, 8);

    const uint64_t tableEnd = static_cast<uint64_t>(wad->m_infoTableOfs) + static_cast<uint64_t>(wad->m_nbLumps) * 16u;

    if (tableEnd > static_cast<uint64_t>(fileSize)) return std::unexpected(WadError::CorruptDirectory);

    return wad;
}

std::span<const std::byte> WadFile::readLump(const WadDirEntry& entry) const {
    return std::span(m_data).subspan(entry.filePos, entry.size);
}