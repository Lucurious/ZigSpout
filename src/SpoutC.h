#include <stdbool.h>
#include <windows.h>
#include <dxgiformat.h> // for DXGI_FORMAT enum
#include <d3d11.h> // For ID3D11Texture2D

#ifdef __cplusplus
#include "SpoutLibrary.h" // Include the C++ header for the Spout library
extern "C" {
#else
typedef struct SPOUTLIBRARY* SPOUTHANDLE; // For C compatibility
typedef int GLint;
typedef unsigned int GLuint;
typedef unsigned int GLenum;

#ifndef GL_RGBA
#define GL_RGBA 0x1908
#endif
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif

enum SpoutLibLogLevel {
	SPOUT_LOG_SILENT,
	SPOUT_LOG_VERBOSE,
	SPOUT_LOG_NOTICE,
	SPOUT_LOG_WARNING,
	SPOUT_LOG_ERROR,
	SPOUT_LOG_FATAL,
	SPOUT_LOG_NONE
};


SPOUTHANDLE WINAPI GetSpout(VOID);
#endif


//
// Sender
//

//   (default: sendername = NULL)
void SetSenderName(SPOUTHANDLE handle, const char* sendername);
// Set the sender DX11 shared texture format
void SetSenderFormat(SPOUTHANDLE handle, DWORD dwFormat);
// Close sender and free resources
//   (default: dwMsec = 0)
//   A sender is created or updated by all sending functions
void ReleaseSender(SPOUTHANDLE handle, DWORD dwMsec);
// Send texture attached to fbo
//   (default: bInvert = true)
//   The fbo must be currently bound
//   The sending texture can be larger than the size that the sender is set up for
//   For example, if the application is using only a portion of the allocated texture space,  
//   such as for Freeframe plugins. (SPOUTHANDLE handle, The 2.006 equivalent is DrawToSharedTexture)
//   To send the OpenGL default framebuffer, specify "0" for the fbo ID, width and height.
bool SendFbo(SPOUTHANDLE handle, GLuint FboID, unsigned int width, unsigned int height, bool bInvert);
// Send OpenGL texture
//   (default: bInvert = true, HostFBO = 0)
bool SendTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, unsigned int width, unsigned int height, bool bInvert, GLuint HostFBO);
// Send image pixels
//   (default: glFormat = GL_RGBA, bInvert = false)
bool SendImage(SPOUTHANDLE handle, const unsigned char* pixels, unsigned int width, unsigned int height, GLenum glFormat, bool bInvert);
// Sender name
const char * GetName(SPOUTHANDLE handle);
// Sender width
unsigned int GetWidth(SPOUTHANDLE handle);
// Sender height
unsigned int GetHeight(SPOUTHANDLE handle);
// Sender frame rate
double GetFps(SPOUTHANDLE handle);
// Sender frame number
long GetFrame(SPOUTHANDLE handle);
// Sender share handle
HANDLE GetHandle(SPOUTHANDLE handle);
// Sender sharing method
bool GetCPU(SPOUTHANDLE handle);
// Sender GL/DX hardware compatibility
bool GetGLDX(SPOUTHANDLE handle);

//
// Receiver
//

// Specify sender for connection
//   (default: ReceiverName = NULL)
//   If a name is specified, the receiver will not connect to any other unless the user selects one
//   If that sender closes, the receiver will wait for the nominated sender to open 
//   If no name is specified, the receiver will connect to the active sender
void SetReceiverName(SPOUTHANDLE handle, const char* ReceiverName);
// Close receiver and release resources ready to connect to another sender
void ReleaseReceiver(SPOUTHANDLE handle);
// Receive texture
//   (default: TextureID = 0, TextureTarget = 0, bInvert = false, HostFbo = 0)
//   If no arguments, connect to a sender and retrieve texture details ready for access
//	 (SPOUTHANDLE handle, see BindSharedTexture and UnBindSharedTexture)
// 	 Connect to a sender and inform the application to update
//   the receiving texture if it has changed dimensions
//   For no change, copy the sender shared texture to the application texture
bool ReceiveTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, bool bInvert, GLuint HostFbo);
// Receive image pixels
//   (default: glFormat = GL_RGBA, bInvert = false, HostFbo = 0)
//   Connect to a sender and inform the application to update
//   the receiving buffer if it has changed dimensions
//   For no change, copy the sender shared texture to the pixel buffer
bool ReceiveImage(SPOUTHANDLE handle, unsigned char *pixels, GLenum glFormat, bool bInvert, GLuint HostFbo);
// Query whether the sender has changed
//   Checked at every cycle before receiving data
bool IsUpdated(SPOUTHANDLE handle);
// Query sender connection
//   If the sender closes, receiving functions return false,  
bool IsConnected(SPOUTHANDLE handle);
// Query received frame status
//   The receiving texture or pixel buffer is only refreshed if the sender has produced a new frame  
//   This can be queried to process texture data only for new frames
bool IsFrameNew(SPOUTHANDLE handle);
// Get sender name
const char * GetSenderName(SPOUTHANDLE handle);
// Get sender width
unsigned int GetSenderWidth(SPOUTHANDLE handle);
// Get sender height
unsigned int GetSenderHeight(SPOUTHANDLE handle);
// Get sender DirectX texture format
DWORD GetSenderFormat(SPOUTHANDLE handle);
// Get sender frame rate
double GetSenderFps(SPOUTHANDLE handle);
// Get sender frame number
long GetSenderFrame(SPOUTHANDLE handle);
// Received sender share handle
HANDLE GetSenderHandle(SPOUTHANDLE handle);
// Received sender texture
ID3D11Texture2D* GetSenderTexture(SPOUTHANDLE handle);
// Received sender sharing mode
bool GetSenderCPU(SPOUTHANDLE handle);
// Received sender GL/DX compatibility
bool GetSenderGLDX(SPOUTHANDLE handle);
// The path of the host that produced the sender
bool GetHostPath(SPOUTHANDLE handle, const char* sendername, char* hostpath, int maxchars);
// Open sender selection dialog
void SelectSender(SPOUTHANDLE handle);

//
// Frame count
//

// Enable or disable frame counting globally
void SetFrameCount(SPOUTHANDLE handle, bool bEnable);
// Disable frame counting specifically for this application
void DisableFrameCount(SPOUTHANDLE handle);
// Return frame count status
bool IsFrameCountEnabled(SPOUTHANDLE handle);
// Sender frame rate control
void HoldFps(SPOUTHANDLE handle, int fps);
// Get system refresh rate
double GetRefreshRate(SPOUTHANDLE handle);
// Signal sync event 
void SetFrameSync(SPOUTHANDLE handle, const char* SenderName);
// Wait or test for a sync event
//   (default: dwTimeout = 0)
bool WaitFrameSync(SPOUTHANDLE handle, const char *SenderName, DWORD dwTimeout);
// Enable / disable frame sync
//   (default: bSync = true)
void EnableFrameSync(SPOUTHANDLE handle, bool bSync);
// Vertical sync status
int GetVerticalSync(SPOUTHANDLE handle);
// Lock to monitor vertical sync
//   (default: bSync = true)
bool SetVerticalSync(SPOUTHANDLE handle, bool bSync);

//
// Data sharing
//

// Write data
bool WriteMemoryBuffer(SPOUTHANDLE handle, const char *sendername, const char* data, int length);
// Read data
int  ReadMemoryBuffer(SPOUTHANDLE handle, const char* sendername, char* data, int maxlength);
// Create a shared memory buffer
bool CreateMemoryBuffer(SPOUTHANDLE handle, const char *name, int length);
// Delete a shared memory buffer
bool DeleteMemoryBuffer(SPOUTHANDLE handle);
// Get the number of bytes available for data transfer
int GetMemoryBufferSize(SPOUTHANDLE handle, const char *name);

//
// Log utilities
//

// Open console for debugging
void OpenSpoutConsole(SPOUTHANDLE handle);
// Close console
//   (default: bWarning = false)
void CloseSpoutConsole(SPOUTHANDLE handle, bool bWarning);
// Enable spout log to the console
void EnableSpoutLog(SPOUTHANDLE handle);
// Enable spout log to a file with optional append
//   (default: bappend = false)
void EnableSpoutLogFile(SPOUTHANDLE handle, const char* filename, bool bappend);
// Show the log file folder in Windows Explorer
void ShowSpoutLogs(SPOUTHANDLE handle);
// Disable logging
void DisableSpoutLog(SPOUTHANDLE handle);
// Set the current log level
// SPOUT_LOG_SILENT  - Disable all messages
// SPOUT_LOG_VERBOSE - Show all messages
// SPOUT_LOG_NOTICE  - Show information messages - default
// SPOUT_LOG_WARNING - Something might go wrong
// SPOUT_LOG_ERROR   - Something did go wrong
// SPOUT_LOG_FATAL   - Something bad happened
void SetSpoutLogLevel(SPOUTHANDLE handle, enum SpoutLibLogLevel level);
// General purpose log
void SpoutLog(SPOUTHANDLE handle, const char* format, ...);
// Verbose - show log for SPOUT_LOG_VERBOSE or above
void SpoutLogVerbose(SPOUTHANDLE handle, const char* format, ...);
// Notice - show log for SPOUT_LOG_NOTICE or above
void SpoutLogNotice(SPOUTHANDLE handle, const char* format, ...);
// Warning - show log for SPOUT_LOG_WARNING or above
void SpoutLogWarning(SPOUTHANDLE handle, const char* format, ...);
// Error - show log for SPOUT_LOG_ERROR or above
void SpoutLogError(SPOUTHANDLE handle, const char* format, ...);
// Fatal - always show log
void SpoutLogFatal(SPOUTHANDLE handle, const char* format, ...);

//
// MessageBox dialog
//

// MessageBox dialog with optional timeout
//   Used where a Windows MessageBox would interfere with the application GUI
//   The dialog closes itself if a timeout is specified
//int SpoutMessageBox(SPOUTHANDLE handle, const char * message, DWORD dwMilliseconds = 0);
// MessageBox dialog with variable arguments
//int SpoutMessageBox(SPOUTHANDLE handle, const char* caption, const char* format, ...);
// MessageBox dialog with standard arguments
//   Replaces an existing MessageBox call
//int SpoutMessageBox(SPOUTHANDLE handle, HWND hwnd, LPCSTR message, LPCSTR caption, UINT uType, DWORD dwMilliseconds = 0);
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
//void SpoutMessageBoxModeless(SPOUTHANDLE handle, bool bMode = true);
// Window handle for SpoutMessageBox where not specified
//void SpoutMessageBoxWindow(SPOUTHANDLE handle, HWND hWnd);
// Copy text to the clipboard
//bool CopyToClipBoard(SPOUTHANDLE handle, HWND hwnd, const char* caps);

//
// Registry utilities
//
// Read subkey DWORD value
bool ReadDwordFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD *pValue);
// Write subkey DWORD value
bool WriteDwordToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD dwValue);
// Read subkey character string
bool ReadPathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, char *filepath);
// Write subkey character string
bool WritePathToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, const char *filepath);
// Remove subkey value name
bool RemovePathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename);
// Delete a subkey and its values.
//   It must be a subkey of the key that hKey identifies, but it cannot have subkeys.  
//   Note that key names are not case sensitive.  
bool RemoveSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey);
// Find subkey
bool FindSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey);

////
//// Information
////
//// Get SDK version number string e.g. "2.007.000"
//std::string GetSDKversion(SPOUTHANDLE handle);
//// Computer type
//bool IsLaptop(SPOUTHANDLE handle);
// Get the module handle of an executable or dll
HMODULE GetCurrentModule(SPOUTHANDLE handle);
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
void StartTiming(SPOUTHANDLE handle);
double EndTiming(SPOUTHANDLE handle);

// -----------------------------------------

// Initialization status
bool IsInitialized(SPOUTHANDLE handle);
// Bind OpenGL shared texture
bool BindSharedTexture(SPOUTHANDLE handle);
// Un-bind OpenGL shared texture
bool UnBindSharedTexture(SPOUTHANDLE handle);
// OpenGL shared texture ID
GLuint GetSharedTextureID(SPOUTHANDLE handle);

//
// Sender names
//

// Number of senders
int GetSenderCount(SPOUTHANDLE handle);
// Sender item name
//   (default: MaxSize = 256)
bool GetSender(SPOUTHANDLE handle, int index, char* sendername, int MaxSize);
// Find a sender in the list
bool FindSenderName(SPOUTHANDLE handle, const char* sendername);
// Sender information
//bool GetSenderInfo(SPOUTHANDLE handle, const char* sendername, unsigned int &width, unsigned int &height, HANDLE &dxShareHandle, DWORD &dwFormat);
// Current active sender
bool GetActiveSender(SPOUTHANDLE handle, char* Sendername);
// Set sender as active
bool SetActiveSender(SPOUTHANDLE handle, const char* Sendername);
	
//
// Get user registry settings recorded by "SpoutSettings"
// Set them either to the registry or for the application only
//

// Get user buffering mode
bool GetBufferMode(SPOUTHANDLE handle);
// Set application buffering mode
//   (default: bActive = true)
void SetBufferMode(SPOUTHANDLE handle, bool bActive);
// Get user number of pixel buffers
int GetBuffers(SPOUTHANDLE handle);
// Set application number of pixel buffers
void SetBuffers(SPOUTHANDLE handle, int nBuffers);
// Get user Maximum senders allowed
int GetMaxSenders(SPOUTHANDLE handle);
// Set user Maximum senders allowed
void SetMaxSenders(SPOUTHANDLE handle, int maxSenders);

//
// Graphics compatibility
//

// Get auto GPU/CPU share depending on compatibility
bool GetAutoShare(SPOUTHANDLE handle);
// Set auto GPU/CPU share depending on compatibility
//   (default: bAuto = true)
void SetAutoShare(SPOUTHANDLE handle, bool bAuto);
// OpenGL texture share compatibility
bool IsGLDXready(SPOUTHANDLE handle);

//
// Adapter functions
//

// The number of graphics adapters in the system
int GetNumAdapters(SPOUTHANDLE handle);
// Adapter item name
bool GetAdapterName(SPOUTHANDLE handle, int index, char *adaptername, int maxchars);
// Return current adapter name
char * AdapterName(SPOUTHANDLE handle);
// Get adapter index 
int GetAdapter(SPOUTHANDLE handle);

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
int GetPerformancePreference(SPOUTHANDLE handle, const char* path);
// Set the Windows graphics preference for an application
bool SetPerformancePreference(SPOUTHANDLE handle, int preference, const char* path);
// Get the graphics adapter name for a Windows preference
bool GetPreferredAdapterName(SPOUTHANDLE handle, int preference, char* adaptername, int maxchars);
// Set graphics adapter index for a Windows preference
bool SetPreferredAdapter(SPOUTHANDLE handle, int preference);
// Availability of Windows graphics preference
bool IsPreferenceAvailable(SPOUTHANDLE handle);
// Is the path a valid application
bool IsApplicationPath(SPOUTHANDLE handle, const char* path);


//
// OpenGL utilities
//

// Create an OpenGL window and context for situations where there is none.
//   Not used if applications already have an OpenGL context.
//   Always call CloseOpenGL afterwards.
bool CreateOpenGL(SPOUTHANDLE handle);
// Close OpenGL window
bool CloseOpenGL(SPOUTHANDLE handle);
// Copy OpenGL texture with optional invert
//   (default: bInvert = false, HostFBO = 0)
//   Textures must be the same size
bool CopyTexture(SPOUTHANDLE handle, GLuint SourceID, GLuint SourceTarget,
	GLuint DestID, GLuint DestTarget,
	unsigned int width, unsigned int height,
	bool bInvert, GLuint HostFBO);

//
// Formats
//

// Get sender DX11 shared texture format
DXGI_FORMAT GetDX11format(SPOUTHANDLE handle);
// Set sender DX11 shared texture format
void SetDX11format(SPOUTHANDLE handle, DXGI_FORMAT textureformat);
// Return OpenGL compatible DX11 format
DXGI_FORMAT DX11format(SPOUTHANDLE handle, GLint glformat);
// Return DX11 compatible OpenGL format
//   (default: textureformat = DXGI_FORMAT_UNKNOWN)
GLint GLDXformat(SPOUTHANDLE handle, DXGI_FORMAT textureformat);
// Return OpenGL texture internal format
int GLformat(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget);
//// Return OpenGL texture format description
//std::string GLformatName(SPOUTHANDLE handle, GLint glformat = 0);

//
// DirectX utilities
//

bool OpenDirectX(SPOUTHANDLE handle);
void CloseDirectX(SPOUTHANDLE handle);

// Initialize and prepare DirectX 11
//    (default: pDevice = NULL)
bool OpenDirectX11(SPOUTHANDLE handle, void * pDevice);
void CloseDirectX11(SPOUTHANDLE handle);

// Return the class device
void* GetDX11Device(SPOUTHANDLE handle);

// Return the class context
void* GetDX11Context(SPOUTHANDLE handle);
	
// Library release function
void Release(SPOUTHANDLE handle);

#ifdef __cplusplus
}
#endif