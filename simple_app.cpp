#include "simple_app.h"

#include <string>

#include "simple_handler.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
#include "include/cef_app.h"

typedef void(WINAPI * Chrome_CallBack_V8)(CefV8Context *context);

extern HANDLE hEvent;
extern void* v8contextcreate;
extern BOOL isSetProxy;
extern CefString proxyserver;
extern BOOL flash;

SimpleApp::SimpleApp() {
}

void SimpleApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();
	SetEvent(hEvent);
}


void SimpleApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
	if (v8contextcreate) {
		((Chrome_CallBack_V8)v8contextcreate)(context.get());
	}
}

void SimpleApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) {
	//if (process_type.empty()) return;
	//command_line->Reset();
	if(flash)
		command_line->AppendSwitch(L"enable-system-flash");
	//if (isSetUA)
	//	command_line->AppendSwitchWithValue(L"user-agent", useragen);
	if (isSetProxy)
		command_line->AppendSwitchWithValue(L"proxy-server", proxyserver);
}