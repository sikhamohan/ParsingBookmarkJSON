#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Function to retrieve URLs from nested folders in the bookmark JSON
void retrieveUrls(const json& node, std::vector<std::string>& urls) {
    if (node.contains("children")) {
        const auto& children = node["children"];
        for (const auto& child : children) {
            if (child.contains("children")) {
                // Recursive call to handle nested folders
                retrieveUrls(child, urls);
            } else if (child.contains("url")) {
                // Add URL to the vector of URLs
                urls.push_back(child["url"]);
            }
        }
    }
}

int main() {
    std::ifstream file("C:/Users/<user>/AppData/Local/Google/Chrome/User Data/Default/bookmarks.json");
    if (!file) {
        std::cout << "Failed to open bookmarks.json" << std::endl;
        return 1;
    }

    // Parse the bookmarks JSON file
    json bookmarks;
    file >> bookmarks;

    std::vector<std::string> urls;
    // Call the function to retrieve URLs from the bookmarks JSON
    retrieveUrls(bookmarks, urls);

    std::cout << "Retrieved URLs:" << std::endl;
    // Print the retrieved URLs
    for (const auto& url : urls) {
        std::cout << url << std::endl;
    }

    return 0;
}
