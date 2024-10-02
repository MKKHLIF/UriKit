#pragma once

#include <memory>
#include <vector>
#include <string>


namespace prism {
    class Uri {
    public:
        Uri();

        Uri(const Uri& other) = delete;

        Uri& operator=(const Uri& other) = delete;

        Uri& operator=(Uri&& other) = delete;

        Uri(Uri&& other) = delete;

        ~Uri();

        // public interface

        /**
         * This method parses and build the URI object from the given URI string.
         *
         * @param[in] uri The URI string to parse.
         *
         * @return
         *  A boolean value indicating whether the URI string was successfully parsed or not.
         */
        bool parseString(const std::string& uri);

        /**
         *  This method returns the scheme of the URI.
         *
         *  @return
         *      The scheme of the URI.
         *
         *  @retval ""
         *      Returns an empty string if the URI has no scheme.
         */
        std::string getScheme() const;


        /**
         *  This method returns the host of the URI.
         *
         *  @return
         *      The host of the URI.
         *
         *  @retval ""
         *      Returns an empty string if the URI has no host.
         */
        std::string getHost() const;

        /**
         * This method returns the path of the URI as a vector of hierarchical path segments.
         *
         *  @note
         *      Absolute path is marked by an empty string at the beginning of the vector.
         *
         *  @return
         *      The path of the URI as a hierarchical path segments.
         */
        std::vector<std::string> getPath() const;

        // temporary helper functions, made public for easier testing purposes...
        static std::string parseScheme(const std::string& uri);

        static std::string parseAuthority(const std::string& uri);

        static std::vector<std::string> parsePath(const std::string& uri);

        static std::string parseHost(const std::string& authority);

        static std::string parsePort(const std::string& authority);

        static std::string parseUserInfo(const std::string& authority);

    private:
        struct UriImpl;

        // exclusively owns the pimpl object it points to.
        std::unique_ptr<struct UriImpl> pimpl_;
    };
}