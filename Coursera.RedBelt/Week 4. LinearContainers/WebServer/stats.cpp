#include "stats.h"

string_view GetToken(string_view& line) {
	size_t pos1 = line.find_first_not_of(' ');
	size_t pos2 = line.find(' ', pos1);
	string_view token = line.substr(pos1, pos2 - pos1);
	line.remove_prefix(pos2 + 1);

	return token;
}

HttpRequest ParseRequest(string_view line)
{
	string_view method = GetToken(line);
	string_view uri = GetToken(line);
	string_view protocol = GetToken(line);

	return { method, uri, protocol };
}

Stats::Stats() : 
	METHODS({ "GET", "PUT", "POST", "DELETE", "UNKNOWN" }), 
	URIS({ "/", "/order", "/product", "/basket", "/help", "unknown"})
{
	for (const auto& method : METHODS) {
		method_stats[method] = 0;
	}

	for (const auto& uri : URIS) {
		uri_stats[uri] = 0;
	}
}

void Stats::AddMethod(string_view method) {
	if (method_stats.count(method)) {
		++method_stats[method];
	}
	else {
		++method_stats["UNKNOWN"];
	}
}

void Stats::AddUri(string_view uri) {
	if (uri_stats.count(uri)) {
		++uri_stats[uri];
	}
	else {
		++uri_stats["unknown"];
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}
