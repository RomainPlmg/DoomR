#include "WadDirectory.hpp"

#include "ByteReader.hpp"
#include "WadFile.hpp"

static std::string nameToString(std::span<const char> raw) {
    size_t len = 0;
    while (len < raw.size() && raw[len] != '\0') ++len;
    return std::string(raw.data(), len);
}

WadDirectory::WadDirectory(const WadFile& file) {
    m_entries.reserve(file.nbLumps());

    for (size_t l = 0; l < file.nbLumps(); ++l) {
        const uint32_t offset = file.infoTableOfs() + l * 16u;

        WadDirEntry entry{};
        entry.filePos = readU32(file.data(), offset);
        entry.size = readU32(file.data(), offset + 4);
        entry.name = readArray8(file.data(), offset + 8);

        m_entries.push_back(entry);
    }
}

const WadDirEntry* WadDirectory::find(std::string_view name) const {
    for (auto it = m_entries.rbegin(); it != m_entries.rend(); it++) {
        if (nameToString(it->name) == name) return &*it;
    }
    return nullptr;
}

std::optional<size_t> WadDirectory::index(std::string_view name) {
    for (size_t i = m_entries.size() - 1; i >= 0; i--) {
        if (nameToString(m_entries[i].name) == name) return i;
    }
    return std::nullopt;
}