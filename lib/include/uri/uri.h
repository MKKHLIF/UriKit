#pragma once

#include <memory>
#include <vector>
#include <string>

class Uri
{
public:
	Uri();
	~Uri();

	Uri(const Uri& other);
	Uri(Uri&& other) noexcept;

	Uri& operator=(const Uri& other);
	Uri& operator=(Uri&& other) noexcept;

	bool operator==(const Uri& other) const;
	bool operator!=(const Uri& other) const;

	[[nodiscard]] bool parse(const std::string& uri) const;

	[[nodiscard]] std::string getScheme() const;

	[[nodiscard]] std::string getHost() const;

	[[nodiscard]] std::vector<std::string> getPath() const;

	[[nodiscard]] uint16_t getPort() const;

	[[nodiscard]] bool hasAuthority() const;

	[[nodiscard]] bool hasPort() const;

	[[nodiscard]] bool hasQuery() const;

	[[nodiscard]] bool hasFragment() const;

	[[nodiscard]] std::string getAuthority() const;

	[[nodiscard]] std::string getUserInfo() const;

	[[nodiscard]] std::string getQuery() const;

	[[nodiscard]] std::string getFragment() const;

	void setScheme(const std::string& scheme);
	void setUserInfo(const std::string& userinfo);
	void setHost(const std::string& host);
	void setPort(uint16_t port);
	void clearPort();
	void setPath(const std::vector<std::string>& path);
	void clearQuery();
	void setQuery(const std::string& query);
	void clearFragment();
	void setFragment(const std::string& fragment);
	[[nodiscard]] std::string generateString() const;

	[[nodiscard]] bool isRelative() const;
	[[nodiscard]] bool containsRelativePath() const;
	void normalizePath();
	[[nodiscard]] Uri resolve(const Uri& relativeReference) const;

private:
	struct UriImpl;
	// exclusively owns the pimpl object it points to.
	std::unique_ptr<UriImpl> pimpl_;
};
