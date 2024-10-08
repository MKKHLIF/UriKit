#pragma once

#include <memory>
#include <vector>
#include <string>

class Uri
{
public:
	Uri();

	Uri(const Uri& other) = delete;

	Uri& operator=(const Uri& other) = delete;

	Uri& operator=(Uri&& other) = delete;

	Uri(Uri&& other) = delete;

	~Uri();

	[[nodiscard]] bool parse(const std::string& uri) const;

	[[nodiscard]] std::string getScheme() const;

	[[nodiscard]] std::string getHost() const;

	[[nodiscard]] std::vector<std::string> getPath() const;

private:
	struct UriImpl;
	// exclusively owns the pimpl object it points to.
	std::unique_ptr<UriImpl> pimpl_;
};
