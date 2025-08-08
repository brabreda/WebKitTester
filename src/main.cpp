#include "webview.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "🚀 Starting WebKit C++ Application..." << std::endl;
    
    // Create WebView instance
    auto webview = std::make_unique<WebView>();
    
    // Initialize the webview
    if (!webview->initialize(1024, 768)) {
        std::cerr << "❌ Failed to initialize WebView" << std::endl;
        return 1;
    }
    
    // Load a test URL
    webview->loadURL("https://www.webkit.org");
    
    // Run the main loop
    webview->run();
    
    std::cout << "✅ Application finished successfully" << std::endl;
    return 0;
}
