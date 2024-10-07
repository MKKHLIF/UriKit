#pragma once

#include <memory>
#include <vector>
#include <string>

class Uri {
public:
	Uri();

	Uri(const Uri& other) = delete;

	Uri& operator=(const Uri& other) = delete;

	Uri& operator=(Uri&& other) = delete;

	Uri(Uri&& other) = delete;

	~Uri();

	bool parse(const std::string& uri) const;

	std::string getScheme() const;

	std::string getHost() const;

	std::vector<std::string> getPath() const;

private:
	struct UriImpl;
	// exclusively owns the pimpl object it points to.
	std::unique_ptr<UriImpl> pimpl_;
};