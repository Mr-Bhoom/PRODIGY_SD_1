#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "gumbo.h"

// Function to write the fetched HTML content to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch(std::bad_alloc &e) {
        return 0;
    }
    return newLength;
}

// Function to fetch HTML content from a given URL
std::string fetchHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string html;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return html;
}

// Function to search for product information in the parsed HTML
void searchForProducts(GumboNode* node, std::vector<std::tuple<std::string, std::string, std::string>>& products) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    GumboAttribute* classAttr;
    if (node->v.element.tag == GUMBO_TAG_DIV &&
        (classAttr = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
        strstr(classAttr->value, "product")) {

        std::string name, price, rating;

        for (int i = 0; i < node->v.element.children.length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(node->v.element.children.data[i]);
            if (child->type != GUMBO_NODE_ELEMENT) continue;

            if (child->v.element.tag == GUMBO_TAG_H2) {
                GumboNode* text = static_cast<GumboNode*>(child->v.element.children.data[0]);
                name = text->v.text.text;
            } else if (child->v.element.tag == GUMBO_TAG_SPAN &&
                       (classAttr = gumbo_get_attribute(&child->v.element.attributes, "class")) &&
                       strstr(classAttr->value, "price")) {
                GumboNode* text = static_cast<GumboNode*>(child->v.element.children.data[0]);
                price = text->v.text.text;
            } else if (child->v.element.tag == GUMBO_TAG_SPAN &&
                       (classAttr = gumbo_get_attribute(&child->v.element.attributes, "class")) &&
                       strstr(classAttr->value, "rating")) {
                GumboNode* text = static_cast<GumboNode*>(child->v.element.children.data[0]);
                rating = text->v.text.text;
            }
        }

        if (!name.empty() && !price.empty() && !rating.empty()) {
            products.emplace_back(name, price, rating);
        }
    }

    for (int i = 0; i < node->v.element.children.length; ++i) {
        searchForProducts(static_cast<GumboNode*>(node->v.element.children.data[i]), products);
    }
}

// Function to parse the HTML content and extract product information
std::vector<std::tuple<std::string, std::string, std::string>> parseHTML(const std::string& html) {
    GumboOutput* output = gumbo_parse(html.c_str());
    std::vector<std::tuple<std::string, std::string, std::string>> products;
    searchForProducts(output->root, products);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    return products;
}

// Function to save the product information to a CSV file
void saveToCSV(const std::vector<std::tuple<std::string, std::string, std::string>>& products, const std::string& filename) {
    std::ofstream file(filename);
    file << "Name,Price,Rating\n";
    for (const auto& product : products) {
        file << std::get<0>(product) << "," << std::get<1>(product) << "," << std::get<2>(product) << "\n";
    }
    file.close();
}

int main() {
    std::string url = "https://www.flipkart.com/";
    std::string html = fetchHTML(url);
    std::vector<std::tuple<std::string, std::string, std::string>> products = parseHTML(html);
    saveToCSV(products, "products.csv");

    std::cout << "Products have been saved to products.csv" << std::endl;
    return 0;
}
