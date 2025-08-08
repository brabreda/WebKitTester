#pragma once

#include <wpe/wpe.h>
#include <wpe/backend-fdo.h>
#include <memory>
#include <string>

class WebView {
public:
    WebView();
    ~WebView();
    
    // Initialize the webview
    bool initialize(int width, int height);
    
    // Load a URL
    void loadURL(const std::string& url);
    
    // Get the WPE view backend
    struct wpe_view_backend* getBackend() const;
    
    // Run the main loop
    void run();

private:
    struct wpe_view_backend* m_backend;
    struct wpe_renderer_backend* m_renderer_backend;
    struct wpe_renderer_host* m_renderer_host;
    
    // WebKit specific members would go here
    // (These would be added when we integrate with WebKit's C API)
};
