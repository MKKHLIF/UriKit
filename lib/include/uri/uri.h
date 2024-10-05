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

	bool parseString(const std::string& uri);

	std::string getScheme() const;

	std::string getHost() const;

	std::vector<std::string> getPath() const;

private:
	class Impl;

	// exclusively owns the pimpl object it points to.
	std::unique_ptr<Impl> pimpl_;
};