#include "webview.h"
#include <wpe/wpe.h>
#include <wpe/backend-fdo.h>
#include <iostream>

WebView::WebView() 
    : m_backend(nullptr)
    , m_renderer_backend(nullptr)
    , m_renderer_host(nullptr) {
}

WebView::~WebView() {
    if (m_renderer_host) {
        wpe_renderer_host_destroy(m_renderer_host);
    }
    if (m_renderer_backend) {
        wpe_renderer_backend_destroy(m_renderer_backend);
    }
    if (m_backend) {
        wpe_view_backend_destroy(m_backend);
    }
}

bool WebView::initialize(int width, int height) {
    // Initialize WPE backend
    m_backend = wpe_view_backend_create();
    if (!m_backend) {
        std::cerr << "Failed to create WPE view backend" << std::endl;
        return false;
    }
    
    // Initialize renderer backend
    m_renderer_backend = wpe_renderer_backend_egl_create();
    if (!m_renderer_backend) {
        std::cerr << "Failed to create WPE renderer backend" << std::endl;
        return false;
    }
    
    // Initialize renderer host
    m_renderer_host = wpe_renderer_host_create(m_renderer_backend);
    if (!m_renderer_host) {
        std::cerr << "Failed to create WPE renderer host" << std::endl;
        return false;
    }
    
    std::cout << "WebView initialized successfully" << std::endl;
    return true;
}

void WebView::loadURL(const std::string& url) {
    std::cout << "Loading URL: " << url << std::endl;
    // TODO: Implement WebKit integration to actually load the URL
}

struct wpe_view_backend* WebView::getBackend() const {
    return m_backend;
}

void WebView::run() {
    std::cout << "Starting WebView main loop..." << std::endl;
    // TODO: Implement main event loop
    // This would typically involve a GLib main loop or similar
}

