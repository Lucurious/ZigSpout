#include "SpoutC.h"

void SetSenderName(SPOUTHANDLE handle) {
    handle->SetSenderName();
}
void SetSenderName(SPOUTHANDLE handle, const char* sendername) {
    handle->SetSenderName(sendername);
}
// Set the sender DX11 shared texture format
void SetSenderFormat(SPOUTHANDLE handle, DWORD dwFormat) {
    handle->SetSenderFormat(dwFormat);
}
// Close sender and free resources
//   A sender is created or updated by all sending functions
void ReleaseSender(SPOUTHANDLE handle) {
    handle->ReleaseSender();
}
void ReleaseSender(SPOUTHANDLE handle, DWORD dwMsec) {
    handle->ReleaseSender(dwMsec);
}
// Send texture attached to fbo
//   The fbo must be currently bound
//   The sending texture can be larger than the size that the sender is set up for
//   For example, if the application is using only a portion of the allocated texture space,  
//   such as for Freeframe plugins. (SPOUTHANDLE handle, The 2.006 equivalent is DrawToSharedTexture)
//   To send the OpenGL default framebuffer, specify "0" for the fbo ID, width and height.
bool SendFbo(SPOUTHANDLE handle, GLuint FboID, unsigned int width, unsigned int height) {
    return handle->SendFbo(FboID, width, height);
}
bool SendFbo(SPOUTHANDLE handle, GLuint FboID, unsigned int width, unsigned int height, bool bInvert) {
    return handle->SendFbo(FboID, width, height, bInvert);
}
// Send OpenGL texture
bool SendTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, unsigned int width, unsigned int height) {
    return handle->SendTexture(TextureID, TextureTarget, width, height);
}
bool SendTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, unsigned int width, unsigned int height, bool bInvert, GLuint HostFBO) {
    return handle->SendTexture(TextureID, TextureTarget, width, height, bInvert, HostFBO);
}
// Send image pixels
bool SendImage(SPOUTHANDLE handle, const unsigned char* pixels, unsigned int width, unsigned int height) {
    return handle->SendImage(pixels, width, height);
}
bool SendImage(SPOUTHANDLE handle, const unsigned char* pixels, unsigned int width, unsigned int height, GLenum glFormat, bool bInvert) {
    return handle->SendImage(pixels, width, height, glFormat, bInvert);
}
// Sender name
const char * GetName(SPOUTHANDLE handle) {
    return handle->GetName();
}
// Sender width
unsigned int GetWidth(SPOUTHANDLE handle) {
    return handle->GetWidth();
}
// Sender height
unsigned int GetHeight(SPOUTHANDLE handle) {
    return handle->GetHeight();
}
// Sender frame rate
double GetFps(SPOUTHANDLE handle) {
    return handle->GetFps();
}
// Sender frame number
long GetFrame(SPOUTHANDLE handle) {
    return handle->GetFrame();
}
// Sender share handle
HANDLE GetHandle(SPOUTHANDLE handle) {
    return handle->GetHandle();
}
// Sender sharing method
bool GetCPU(SPOUTHANDLE handle) {
    return handle->GetCPU();
}
// Sender GL/DX hardware compatibility
bool GetGLDX(SPOUTHANDLE handle) {
    return handle->GetGLDX();
}

//
// Receiver
//

// Specify sender for connection
//   If a name is specified, the receiver will not connect to any other unless the user selects one
//   If that sender closes, the receiver will wait for the nominated sender to open 
//   If no name is specified, the receiver will connect to the active sender
void SetReceiverName(SPOUTHANDLE handle) {
    handle->SetReceiverName();
}
void SetReceiverName(SPOUTHANDLE handle, const char* SenderName) {
    handle->SetReceiverName(SenderName);
}
// Close receiver and release resources ready to connect to another sender
void ReleaseReceiver(SPOUTHANDLE handle) {
    handle->ReleaseReceiver();
}
// Receive texture
//   If no arguments, connect to a sender and retrieve texture details ready for access
//	 (SPOUTHANDLE handle, see BindSharedTexture and UnBindSharedTexture)
// 	 Connect to a sender and inform the application to update
//   the receiving texture if it has changed dimensions
//   For no change, copy the sender shared texture to the application texture
bool ReceiveTexture(SPOUTHANDLE handle) {
    return handle->ReceiveTexture();
}
bool ReceiveTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, bool bInvert, GLuint HostFbo) {
    return handle->ReceiveTexture(TextureID, TextureTarget, bInvert, HostFbo);
}
// Receive image pixels
//   Connect to a sender and inform the application to update
//   the receiving buffer if it has changed dimensions
//   For no change, copy the sender shared texture to the pixel buffer
bool ReceiveImage(SPOUTHANDLE handle, unsigned char *pixels) {
    return handle->ReceiveImage(pixels);
}
bool ReceiveImage(SPOUTHANDLE handle, unsigned char *pixels, GLenum glFormat, bool bInvert, GLuint HostFbo) {
    return handle->ReceiveImage(pixels, glFormat, bInvert, HostFbo);
}
// Query whether the sender has changed
//   Checked at every cycle before receiving data
bool IsUpdated(SPOUTHANDLE handle) {
    return handle->IsUpdated();
}
// Query sender connection
//   If the sender closes, receiving functions return false,
bool IsConnected(SPOUTHANDLE handle) {
    return handle->IsConnected();
}
// Query received frame status
//   The receiving texture or pixel buffer is only refreshed if the sender has produced a new frame  
//   This can be queried to process texture data only for new frames
bool IsFrameNew(SPOUTHANDLE handle) {
    return handle->IsFrameNew();
}
// Get sender name
const char * GetSenderName(SPOUTHANDLE handle) {
    return handle->GetSenderName();
}
// Get sender width
unsigned int GetSenderWidth(SPOUTHANDLE handle) {
    return handle->GetSenderWidth();
}
// Get sender height
unsigned int GetSenderHeight(SPOUTHANDLE handle) {
    return handle->GetSenderHeight();
}
// Get sender DirectX texture format
DWORD GetSenderFormat(SPOUTHANDLE handle) {
    return handle->GetSenderFormat();
}
// Get sender frame rate
double GetSenderFps(SPOUTHANDLE handle) {
    return handle->GetSenderFps();
}
// Get sender frame number
long GetSenderFrame(SPOUTHANDLE handle) {
    return handle->GetSenderFrame();
}
// Received sender share handle
HANDLE GetSenderHandle(SPOUTHANDLE handle) {
    return handle->GetSenderHandle();
}
// Received sender texture
ID3D11Texture2D* GetSenderTexture(SPOUTHANDLE handle) {
    return handle->GetSenderTexture();
}
// Received sender sharing mode
bool GetSenderCPU(SPOUTHANDLE handle) {
    return handle->GetSenderCPU();
}
// Received sender GL/DX compatibility
bool GetSenderGLDX(SPOUTHANDLE handle) {
    return handle->GetSenderGLDX();
}
// The path of the host that produced the sender
bool GetHostPath(SPOUTHANDLE handle, const char* sendername, char* hostpath, int maxchars) {
    return handle->GetHostPath(sendername, hostpath, maxchars);
}
// Open sender selection dialog
void SelectSender(SPOUTHANDLE handle) {
    handle->SelectSender();
}

//
// Frame count
//

// Enable or disable frame counting globally
void SetFrameCount(SPOUTHANDLE handle, bool bEnable) {
    handle->SetFrameCount(bEnable);
}
// Disable frame counting specifically for this application
void DisableFrameCount(SPOUTHANDLE handle) {
    handle->DisableFrameCount();
}
// Return frame count status
bool IsFrameCountEnabled(SPOUTHANDLE handle) {
    return handle->IsFrameCountEnabled();
}
// Sender frame rate control
void HoldFps(SPOUTHANDLE handle, int fps) {
    handle->HoldFps(fps);
}
// Get system refresh rate
double GetRefreshRate(SPOUTHANDLE handle) {
    return handle->GetRefreshRate();
}
// Signal sync event 
void SetFrameSync(SPOUTHANDLE handle, const char* SenderName) {
    handle->SetFrameSync(SenderName);
}
// Wait or test for a sync event
bool WaitFrameSync(SPOUTHANDLE handle, const char *SenderName, DWORD dwTimeout) {
    return handle->WaitFrameSync(SenderName, dwTimeout);
}
// Enable / disable frame sync
void EnableFrameSync(SPOUTHANDLE handle, bool bSync) {
    handle->EnableFrameSync(bSync);
}
// Vertical sync status
int GetVerticalSync(SPOUTHANDLE handle) {
    return handle->GetVerticalSync();
}
// Lock to monitor vertical sync
bool SetVerticalSync(SPOUTHANDLE handle, bool bSync) {
    return handle->SetVerticalSync(bSync);
}

//
// Data sharing
//

// Write data
bool WriteMemoryBuffer(SPOUTHANDLE handle, const char *sendername, const char* data, int length) {
    return handle->WriteMemoryBuffer(sendername, data, length);
}
// Read data
int  ReadMemoryBuffer(SPOUTHANDLE handle, const char* sendername, char* data, int maxlength) {
    return handle->ReadMemoryBuffer(sendername, data, maxlength);
}
// Create a shared memory buffer
bool CreateMemoryBuffer(SPOUTHANDLE handle, const char *name, int length) {
    return handle->CreateMemoryBuffer(name, length);
}
// Delete a shared memory buffer
bool DeleteMemoryBuffer(SPOUTHANDLE handle) {
    return handle->DeleteMemoryBuffer();
}
// Get the number of bytes available for data transfer
int GetMemoryBufferSize(SPOUTHANDLE handle, const char *name) {
    return handle->GetMemoryBufferSize(name);
}

//
// Log utilities
//

// Open console for debugging
void OpenSpoutConsole(SPOUTHANDLE handle) {
    handle->OpenSpoutConsole();
}
// Close console
void CloseSpoutConsole(SPOUTHANDLE handle, bool bWarning) {
    handle->CloseSpoutConsole(bWarning);
}
// Enable spout log to the console
void EnableSpoutLog(SPOUTHANDLE handle) {
    handle->EnableSpoutLog();
}
// Enable spout log to a file with optional append
void EnableSpoutLogFile(SPOUTHANDLE handle, const char* filename, bool bappend) {
    handle->EnableSpoutLogFile(filename, bappend);
}
// Show the log file folder in Windows Explorer
void ShowSpoutLogs(SPOUTHANDLE handle) {
    handle->ShowSpoutLogs();
}
// Disable logging
void DisableSpoutLog(SPOUTHANDLE handle) {
    handle->DisableSpoutLog();
}
// Set the current log level
// SPOUT_LOG_SILENT  - Disable all messages
// SPOUT_LOG_VERBOSE - Show all messages
// SPOUT_LOG_NOTICE  - Show information messages - default
// SPOUT_LOG_WARNING - Something might go wrong
// SPOUT_LOG_ERROR   - Something did go wrong
// SPOUT_LOG_FATAL   - Something bad happened
void SetSpoutLogLevel(SPOUTHANDLE handle, enum SpoutLibLogLevel level) {
    handle->SetSpoutLogLevel(level);
}   
// General purpose log
void SpoutLog(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLog(format, args);
    va_end(args);
}
// Verbose - show log for SPOUT_LOG_VERBOSE or above
void SpoutLogVerbose(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLogVerbose(format, args);
    va_end(args);
}
// Notice - show log for SPOUT_LOG_NOTICE or above
void SpoutLogNotice(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLogNotice(format, args);
    va_end(args);
}
// Warning - show log for SPOUT_LOG_WARNING or above
void SpoutLogWarning(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLogWarning(format, args);
    va_end(args);
}
// Error - show log for SPOUT_LOG_ERROR or above
void SpoutLogError(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLogError(format, args);
    va_end(args);
}
// Fatal - always show log
void SpoutLogFatal(SPOUTHANDLE handle, const char* format, ...) {
    va_list args;
    va_start(args, format);
    handle->SpoutLogFatal(format, args);
    va_end(args);
}

//
// MessageBox dialog
//

// MessageBox dialog with optional timeout
//   Used where a Windows MessageBox would interfere with the application GUI
//   The dialog closes itself if a timeout is specified
//int SpoutMessageBox(SPOUTHANDLE handle, const char * message, DWORD dwMilliseconds);
// MessageBox dialog with variable arguments
//int SpoutMessageBox(SPOUTHANDLE handle, const char* caption, const char* format, ...);
// MessageBox dialog with standard arguments
//   Replaces an existing MessageBox call
//int SpoutMessageBox(SPOUTHANDLE handle, HWND hwnd, LPCSTR message, LPCSTR caption, UINT uType, DWORD dwMilliseconds);
// MessageBox dialog with an edit control for text input
//int SpoutMessageBox(SPOUTHANDLE handle, HWND hwnd, LPCSTR message, LPCSTR caption, UINT uType, std::string& text);
//// MessageBox dialog with a combobox control for item selection
//int SpoutMessageBox(SPOUTHANDLE handle, HWND hwnd, LPCSTR message, LPCSTR caption, UINT uType, std::vector<std::string> items, int& selected);
// Custom icon for SpoutMessageBox from resources
//void SpoutMessageBoxIcon(SPOUTHANDLE handle, HICON hIcon);
//// Custom icon for SpoutMessageBox from file
//bool SpoutMessageBoxIcon(SPOUTHANDLE handle, std::string iconfile);
//// Custom button for SpoutMessageBox
//void SpoutMessageBoxButton(SPOUTHANDLE handle, int ID, std::wstring title);
// Activate modeless mode using SpoutPanel.exe
//void SpoutMessageBoxModeless(SPOUTHANDLE handle, bool bMode);
// Window handle for SpoutMessageBox where not specified
//void SpoutMessageBoxWindow(SPOUTHANDLE handle, HWND hWnd);
// Copy text to the clipboard
//bool CopyToClipBoard(SPOUTHANDLE handle, HWND hwnd, const char* caps);

//
// Registry utilities
//
// Read subkey DWORD value
bool ReadDwordFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD *pValue) {
    return handle->ReadDwordFromRegistry(hKey, subkey, valuename, pValue);
}
// Write subkey DWORD value
bool WriteDwordToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD dwValue) {
    return handle->WriteDwordToRegistry(hKey, subkey, valuename, dwValue);
}

// Read subkey character string
bool ReadPathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, char *filepath) {
    return handle->ReadPathFromRegistry(hKey, subkey, valuename, filepath);
}

// Write subkey character string
bool WritePathToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, const char *filepath) {
    return handle->WritePathToRegistry(hKey, subkey, valuename, filepath);
}

// Remove subkey value name
bool RemovePathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename) {
    return handle->RemovePathFromRegistry(hKey, subkey, valuename);
}
// Delete a subkey and its values.
//   It must be a subkey of the key that hKey identifies, but it cannot have subkeys.  
//   Note that key names are not case sensitive.  
bool RemoveSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey) {
    return handle->RemoveSubKey(hKey, subkey);
}
// Find subkey
bool FindSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey) {
    return handle->FindSubKey(hKey, subkey);
}

////
//// Information
////
//// Get SDK version number string e.g. "2.007.000"
//std::string GetSDKversion(SPOUTHANDLE handle);
//// Computer type
//bool IsLaptop(SPOUTHANDLE handle);
// Get the module handle of an executable or dll
HMODULE GetCurrentModule(SPOUTHANDLE handle) {
    return handle->GetCurrentModule();
}
//// Get executable or dll version
//std::string GetExeVersion(SPOUTHANDLE handle, const char* path);
//// Get executable or dll path
//std::string GetExePath(SPOUTHANDLE handle);
//// Get executable or dll name
//std::string GetExeName(SPOUTHANDLE handle);
//// Remove path and return the file name
//void RemovePath(SPOUTHANDLE handle, std::string& path);
//// Remove file name and return the path
//void RemoveName(SPOUTHANDLE handle, std::string& path);

//
// Timing utilities
//
void StartTiming(SPOUTHANDLE handle) {
    handle->StartTiming();
}
double EndTiming(SPOUTHANDLE handle) {
    return handle->EndTiming();
}

// -----------------------------------------

// Initialization status
bool IsInitialized(SPOUTHANDLE handle) {
    return handle->IsInitialized();
}

// Bind OpenGL shared texture
bool BindSharedTexture(SPOUTHANDLE handle) {
    return handle->BindSharedTexture();
}
// Un-bind OpenGL shared texture
bool UnBindSharedTexture(SPOUTHANDLE handle) {
    return handle->UnBindSharedTexture();
}
// OpenGL shared texture ID
GLuint GetSharedTextureID(SPOUTHANDLE handle) {
    return handle->GetSharedTextureID();
}

//
// Sender names
//

// Number of senders
int GetSenderCount(SPOUTHANDLE handle) {
    return handle->GetSenderCount();
}
// Sender item name
bool GetSender(SPOUTHANDLE handle, int index, char* sendername, int MaxSize) {
    return handle->GetSender(index, sendername, MaxSize);
}
// Find a sender in the list
bool FindSenderName(SPOUTHANDLE handle, const char* sendername) {
    return handle->FindSenderName(sendername);
}
// Sender information
//bool GetSenderInfo(SPOUTHANDLE handle, const char* sendername, unsigned int &width, unsigned int &height, HANDLE &dxShareHandle, DWORD &dwFormat);
// Current active sender
bool GetActiveSender(SPOUTHANDLE handle, char* Sendername) {
    return handle->GetActiveSender(Sendername);
}
// Set sender as active
bool SetActiveSender(SPOUTHANDLE handle, const char* Sendername) {
    return handle->SetActiveSender(Sendername);
}
	
//
// Get user registry settings recorded by "SpoutSettings"
// Set them either to the registry or for the application only
//

// Get user buffering mode
bool GetBufferMode(SPOUTHANDLE handle) {
    return handle->GetBufferMode();
}
// Set application buffering mode
void SetBufferMode(SPOUTHANDLE handle, bool bActive) {
    handle->SetBufferMode(bActive);
}
// Get user number of pixel buffers
int GetBuffers(SPOUTHANDLE handle) {
    return handle->GetBuffers();
}
// Set application number of pixel buffers
void SetBuffers(SPOUTHANDLE handle, int nBuffers) {
    handle->SetBuffers(nBuffers);
}
// Get user Maximum senders allowed
int GetMaxSenders(SPOUTHANDLE handle) {
    return handle->GetMaxSenders();
}
// Set user Maximum senders allowed
void SetMaxSenders(SPOUTHANDLE handle, int maxSenders) {
    handle->SetMaxSenders(maxSenders);
}

//
// Graphics compatibility
//

// Get auto GPU/CPU share depending on compatibility
bool GetAutoShare(SPOUTHANDLE handle) {
    return handle->GetAutoShare();
}
// Set auto GPU/CPU share depending on compatibility
void SetAutoShare(SPOUTHANDLE handle, bool bAuto) {
    handle->SetAutoShare(bAuto);
}
// OpenGL texture share compatibility
bool IsGLDXready(SPOUTHANDLE handle) {
    return handle->IsGLDXready();
}

//
// Adapter functions
//

// The number of graphics adapters in the system
int GetNumAdapters(SPOUTHANDLE handle) {
    return handle->GetNumAdapters();
}
// Adapter item name
bool GetAdapterName(SPOUTHANDLE handle, int index, char *adaptername, int maxchars) {
    return handle->GetAdapterName(index, adaptername, maxchars);
}
// Return current adapter name
char * AdapterName(SPOUTHANDLE handle) {
    return handle->AdapterName();
}
// Get adapter index
int GetAdapter(SPOUTHANDLE handle) {
    return handle->GetAdapter();
}

//
// Graphics preference
//
// Windows 10+ SDK required
//#ifdef NTDDI_WIN10_RS4

// Get the Windows graphics preference for an application
//	-1 - Not registered
//	 0 - Let Windows decide  DXGI_GPU_PREFERENCE_UNSPECIFIED
//	 1 - Power saving        DXGI_GPU_PREFERENCE_MINIMUM_POWER
//	 2 - High performance    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE
int GetPerformancePreference(SPOUTHANDLE handle, const char* path) {
    return handle->GetPerformancePreference(path);
}
// Set the Windows graphics preference for an application
bool SetPerformancePreference(SPOUTHANDLE handle, int preference, const char* path) {
    return handle->SetPerformancePreference(preference, path);
}
// Get the graphics adapter name for a Windows preference
bool GetPreferredAdapterName(SPOUTHANDLE handle, int preference, char* adaptername, int maxchars) {
    return handle->GetPreferredAdapterName(preference, adaptername, maxchars);
}
// Set graphics adapter index for a Windows preference
bool SetPreferredAdapter(SPOUTHANDLE handle, int preference) {
    return handle->SetPreferredAdapter(preference);
}
// Availability of Windows graphics preference
bool IsPreferenceAvailable(SPOUTHANDLE handle) {
    return handle->IsPreferenceAvailable();
}
// Is the path a valid application
bool IsApplicationPath(SPOUTHANDLE handle, const char* path) {
    return handle->IsApplicationPath(path);
}


//
// OpenGL utilities
//

// Create an OpenGL window and context for situations where there is none.
//   Not used if applications already have an OpenGL context.
//   Always call CloseOpenGL afterwards.
bool CreateOpenGL(SPOUTHANDLE handle) {
    return handle->CreateOpenGL();
}
// Close OpenGL window
bool CloseOpenGL(SPOUTHANDLE handle) {
    return handle->CloseOpenGL();
}
// Copy OpenGL texture with optional invert
//   Textures must be the same size
bool CopyTexture(SPOUTHANDLE handle, GLuint SourceID, GLuint SourceTarget,
	GLuint DestID, GLuint DestTarget,
	unsigned int width, unsigned int height,
	bool bInvert, GLuint HostFBO) {
    return handle->CopyTexture(SourceID, SourceTarget, DestID, DestTarget, width, height, bInvert, HostFBO);
}

//
// Formats
//

// Get sender DX11 shared texture format
DXGI_FORMAT GetDX11format(SPOUTHANDLE handle) {
    return handle->GetDX11format();
}
// Set sender DX11 shared texture format
void SetDX11format(SPOUTHANDLE handle, DXGI_FORMAT textureformat) {
    handle->SetDX11format(textureformat);
}
// Return OpenGL compatible DX11 format
DXGI_FORMAT DX11format(SPOUTHANDLE handle, GLint glformat) {
    return handle->DX11format(glformat);
}
// Return DX11 compatible OpenGL format
GLint GLDXformat(SPOUTHANDLE handle, DXGI_FORMAT textureformat) {
    return handle->GLDXformat(textureformat);
}
// Return OpenGL texture internal format
int GLformat(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget) {
    return handle->GLformat(TextureID, TextureTarget);
}
// Return OpenGL texture format description
//std::string GLformatName(SPOUTHANDLE handle, GLint glformat);

//
// DirectX utilities
//

bool OpenDirectX(SPOUTHANDLE handle) {
    return handle->OpenDirectX();
}
void CloseDirectX(SPOUTHANDLE handle) {
    handle->CloseDirectX();
}

// Initialize and prepare DirectX 11
bool OpenDirectX11(SPOUTHANDLE handle, void * pDevice) {
    return handle->OpenDirectX11(pDevice);
}
void CloseDirectX11(SPOUTHANDLE handle) {
    handle->CloseDirectX11();
}

// Return the class device
void* GetDX11Device(SPOUTHANDLE handle) {
    return handle->GetDX11Device();
}

// Return the class context
void* GetDX11Context(SPOUTHANDLE handle) {
    return handle->GetDX11Context();
}
	
// Library release function
void Release(SPOUTHANDLE handle) {
    handle->Release();
}
