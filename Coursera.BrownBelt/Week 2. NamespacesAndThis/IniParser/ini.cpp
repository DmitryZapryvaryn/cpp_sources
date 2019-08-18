#include "ini.h"

#include <string_view>
#include <tuple>

namespace Ini {

	Section& Document::AddSection(std::string name)
	{
		return sections[name];
	}

	const Section& Document::GetSection(const std::string& name) const
	{
		return sections.at(name);
	}

	size_t Document::SectionCount() const
	{
		return sections.size();
	}

	std::pair<std::string, std::string> ParseKeyValuePair(std::string_view line) {
		std::string key;
		std::string value;

		std::size_t delim_pos = line.find('=');
		key = line.substr(0, delim_pos);
		value = line.substr(delim_pos+1);

		return { key, value };
	}

	std::string ParseSectionName(std::string_view line) {
		line.remove_prefix(1);
		line.remove_suffix(1);

		return std::string(line.begin(), line.end());
	}

	Document Load(std::istream& input)
	{
		Document result_doc;

		std::string line;
		std::getline(input, line);
		if (!line.empty()) {
			Section* section = &result_doc.AddSection(ParseSectionName(line));
			while (std::getline(input, line)) {
				if (!line.empty()) {
					if (line.front() == '[') {
						section = &result_doc.AddSection(ParseSectionName(line));
					}
					else {
						section->insert(ParseKeyValuePair(line));
					}
				}
			}
		}

		return result_doc;
	}

} // end Ini