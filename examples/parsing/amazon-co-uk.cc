#include <iostream>
#include <iomanip>
#include <uri/uri.h>


void printUriParts(const Uri& uri) {
    auto printBox = [](const std::string& title, const std::string& content) {
        std::cout << "+-----------------------------+" << std::endl;
        std::cout << "| " << std::setw(27) << std::left << title << " |" << std::endl;
        std::cout << "+-----------------------------+" << std::endl;
        std::cout << "| " << std::setw(27) << std::left << content << " |" << std::endl;
        std::cout << "+-----------------------------+" << std::endl;
    };

    printBox("Scheme", uri.getScheme());
    printBox("Host", uri.getHost());
    printBox("Authority", uri.getAuthority());
    printBox("User Info", uri.getUserInfo());
    printBox("Port", std::to_string(uri.getPort()));

    std::string path;
    for (const auto& segment : uri.getPath()) {
        path += "/" + segment;
    }
    printBox("Path", path);

    printBox("Query", uri.getQuery());
    printBox("Fragment", uri.getFragment());
}


int main() {
    const Uri uri;
    bool rs = uri.parse("https://www.amazon.co.uk/Calvin-Klein-Womens-CW84M779-Jacket/dp/B08RZ9GPVX/ref=sr_1_3?content-id=amzn1.sym.e65d6805-d09d-4443-9832-0879d5e24654%3Aamzn1.sym.e65d6805-d09d-4443-9832-0879d5e24654&dib=eyJ2IjoiMSJ9.XxUIkld-X7Ddou651v4hO1Cz08Vy9kHhP7qhVKK3q6BV5JAiRsy2jdcbbCaGkF9w._OuGeKWBCNM9LHDu-Ohtf3I00vVkemjRHtXDBVdhbQs&dib_tag=se&nsdOptOutParam=true&pd_rd_r=00bd77c9-b691-4f29-8701-5d50443b2822&pd_rd_w=F1Xph&pd_rd_wg=fmaJZ&pf_rd_p=e65d6805-d09d-4443-9832-0879d5e24654&pf_rd_r=BMM6AAZJ19H7PBS04HRG&qid=1731261533&rnid=1731296031&s=apparel&sr=1-3&wi=m0gwu5vg_3&th=1");
    if (rs) {
        std::cout << "\nParsed successfully" << std::endl;
        printUriParts(uri);
    } else {
        std::cout << "Failed to parse" << std::endl;
    }

    rs = uri.parse("https://codeforces.com/profile/--MK--?csrf_token=354c5900b9bff2f852de0ca040a26323");

    if (rs) {
        std::cout << "\nParsed successfully" << std::endl;
        printUriParts(uri);
    } else {
        std::cout << "Failed to parse" << std::endl;
    }

    return 0;
}