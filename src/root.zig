const std = @import("std");

const spoutc = @cImport({
    @cInclude("SpoutC.h");
});

pub const SPOUTHANDLE = *spoutc.struct_SPOUTLIBRARY;

pub fn GetSpout() !Spout {
    const spout_opt = spoutc.GetSpout();
    if (spout_opt) |spout| {
        return Spout{ .handle = spout };
    } else {
        return error.SpoutNotAvailable;
    }
}

pub const Spout = struct {
    handle: SPOUTHANDLE,

    // (default: sendername = NULL)
    // void SetSenderName(SPOUTHANDLE handle, const char* sendername);
    pub fn SetSenderName(self: Spout, sender_name: [:0]const u8) void {
        spoutc.SetSenderName(self.handle, sender_name);
    }

    // Set the sender DX11 shared texture format
    // void SetSenderFormat(SPOUTHANDLE handle, DWORD dwFormat);
    pub fn SetSenderFormat(self: Spout, format: spoutc.DWORD) void {
        spoutc.SetSenderFormat(self.handle, format);
    }

    // Close sender and free resources
    //   (default: dwMsec = 0)
    //   A sender is created or updated by all sending functions
    // void ReleaseSender(SPOUTHANDLE handle, DWORD dwMsec);
    pub fn ReleaseSender(self: Spout, dwMsec: spoutc.DWORD) void {
        spoutc.ReleaseSender(self.handle, dwMsec);
    }

    // Send texture attached to fbo
    //   (default: bInvert = true)
    //   The fbo must be currently bound
    //   The sending texture can be larger than the size that the sender is set up for
    //   For example, if the application is using only a portion of the allocated texture space,
    //   such as for Freeframe plugins. (SPOUTHANDLE handle, The 2.006 equivalent is DrawToSharedTexture)
    //   To send the OpenGL default framebuffer, specify "0" for the fbo ID, width and height.
    // bool SendFbo(SPOUTHANDLE handle, GLuint FboID, unsigned int width, unsigned int height, bool bInvert);
    pub fn SendFbo(self: Spout, fbo: spoutc.GLuint, width: c_uint, height: c_uint, bInvert: bool) bool {
        return spoutc.SendFbo(self.handle, fbo, width, height, bInvert);
    }

    // Send OpenGL texture
    //   (default: bInvert = true, HostFBO = 0)
    // bool SendTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, unsigned int width, unsigned int height, bool bInvert, GLuint HostFBO);
    pub fn SendTexture(self: Spout, texture: spoutc.GLuint, target: spoutc.GLuint, width: c_uint, height: c_uint, bInvert: bool) bool {
        return spoutc.SendTexture(self.handle, texture, target, width, height, bInvert);
    }

    // Send image pixels
    //   (default: glFormat = GL_RGBA, bInvert = false)
    // bool SendImage(SPOUTHANDLE handle, const unsigned char* pixels, unsigned int width, unsigned int height, GLenum glFormat, bool bInvert);
    pub fn SendImage(self: Spout, pixels: []const u8, width: c_uint, height: c_uint, glFormat: spoutc.GLenum, bInvert: bool) bool {
        return spoutc.SendImage(self.handle, pixels, width, height, glFormat, bInvert);
    }

    // Sender name
    //const char* GetName(SPOUTHANDLE handle);
    pub fn GetName(self: Spout) [:0]const u8 {
        return spoutc.GetName(self.handle);
    }

    // Sender width
    // unsigned int GetWidth(SPOUTHANDLE handle);
    pub fn GetWidth(self: Spout) c_uint {
        return spoutc.GetWidth(self.handle);
    }
    // Sender height
    // unsigned int GetHeight(SPOUTHANDLE handle);
    pub fn GetHeight(self: Spout) c_uint {
        return spoutc.GetHeight(self.handle);
    }
    // Sender frame rate
    // double GetFps(SPOUTHANDLE handle);
    pub fn GetFps(self: Spout) f64 {
        return spoutc.GetFps(self.handle);
    }
    // Sender frame number
    // long GetFrame(SPOUTHANDLE handle);
    pub fn GetFrame(self: Spout) c_long {
        return spoutc.GetFrame(self.handle);
    }
    // Sender share handle
    // HANDLE GetHandle(SPOUTHANDLE handle);
    pub fn GetHandle(self: Spout) spoutc.HANDLE {
        return spoutc.GetHandle(self.handle);
    }
    // Sender sharing method
    // bool GetCPU(SPOUTHANDLE handle);
    pub fn GetCPU(self: Spout) bool {
        return spoutc.GetCPU(self.handle);
    }
    // Sender GL/DX hardware compatibility
    // bool GetGLDX(SPOUTHANDLE handle);
    pub fn GetGLDX(self: Spout) bool {
        return spoutc.GetGLDX(self.handle);
    }

    //
    // Receiver
    //

    // Specify sender for connection
    //   (default: ReceiverName = NULL)
    //   If a name is specified, the receiver will not connect to any other unless the user selects one
    //   If that sender closes, the receiver will wait for the nominated sender to open
    //   If no name is specified, the receiver will connect to the active sender
    // void SetReceiverName(SPOUTHANDLE handle, const char* ReceiverName);
    pub fn SetReceiverName(self: Spout, receiver_name: [:0]const u8) void {
        spoutc.SetReceiverName(self.handle, receiver_name);
    }
    // Close receiver and release resources ready to connect to another sender
    // void ReleaseReceiver(SPOUTHANDLE handle);
    pub fn ReleaseReceiver(self: Spout) void {
        spoutc.ReleaseReceiver(self.handle);
    }
    // Receive texture
    //   (default: TextureID = 0, TextureTarget = 0, bInvert = false, HostFbo = 0)
    //   If no arguments, connect to a sender and retrieve texture details ready for access
    //   (SPOUTHANDLE handle, see BindSharedTexture and UnBindSharedTexture)
    //   Connect to a sender and inform the application to update
    //   the receiving texture if it has changed dimensions
    //   For no change, copy the sender shared texture to the application texture
    // bool ReceiveTexture(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget, bool bInvert, GLuint HostFbo);
    pub fn ReceiveTexture(self: Spout, texture: spoutc.GLuint, target: spoutc.GLuint, bInvert: bool, hostFbo: spoutc.GLuint) bool {
        return spoutc.ReceiveTexture(self.handle, texture, target, bInvert, hostFbo);
    }
    // Receive image pixels
    //   (default: glFormat = GL_RGBA, bInvert = false, HostFbo = 0)
    //   Connect to a sender and inform the application to update
    //   the receiving buffer if it has changed dimensions
    //   For no change, copy the sender shared texture to the pixel buffer
    // bool ReceiveImage(SPOUTHANDLE handle, unsigned char *pixels, GLenum glFormat, bool bInvert, GLuint HostFbo);
    pub fn ReceiveImage(self: Spout, pixels: []u8, glFormat: spoutc.GLenum, bInvert: bool, hostFbo: spoutc.GLuint) bool {
        return spoutc.ReceiveImage(self.handle, pixels, glFormat, bInvert, hostFbo);
    }

    // Query whether the sender has changed
    //   Checked at every cycle before receiving data
    // bool IsUpdated(SPOUTHANDLE handle);
    pub fn IsUpdated(self: Spout) bool {
        return spoutc.IsUpdated(self.handle);
    }

    // Query sender connection
    //   If the sender closes, receiving functions return false,
    // bool IsConnected(SPOUTHANDLE handle);
    pub fn IsConnected(self: Spout) bool {
        return spoutc.IsConnected(self.handle);
    }

    // Query received frame status
    //   The receiving texture or pixel buffer is only refreshed if the sender has produced a new frame
    //   This can be queried to process texture data only for new frames
    // bool IsFrameNew(SPOUTHANDLE handle);
    pub fn IsFrameNew(self: Spout) bool {
        return spoutc.IsFrameNew(self.handle);
    }

    // Get sender name
    // const char * GetSenderName(SPOUTHANDLE handle);
    pub fn GetSenderName(self: Spout) [:0]const u8 {
        return spoutc.GetSenderName(self.handle);
    }

    // Get sender width
    // unsigned int GetSenderWidth(SPOUTHANDLE handle);
    pub fn GetSenderWidth(self: Spout) c_uint {
        return spoutc.GetSenderWidth(self.handle);
    }

    // Get sender height
    // unsigned int GetSenderHeight(SPOUTHANDLE handle);
    pub fn GetSenderHeight(self: Spout) c_uint {
        return spoutc.GetSenderHeight(self.handle);
    }

    // Get sender DirectX texture format
    // DWORD GetSenderFormat(SPOUTHANDLE handle);
    pub fn GetSenderFormat(self: Spout) spoutc.DWORD {
        return spoutc.GetSenderFormat(self.handle);
    }

    // Get sender frame rate
    // double GetSenderFps(SPOUTHANDLE handle);
    pub fn GetSenderFps(self: Spout) f64 {
        return spoutc.GetSenderFps(self.handle);
    }

    // Get sender frame number
    // long GetSenderFrame(SPOUTHANDLE handle);
    pub fn GetSenderFrame(self: Spout) c_long {
        return spoutc.GetSenderFrame(self.handle);
    }

    // Received sender share handle
    // HANDLE GetSenderHandle(SPOUTHANDLE handle);
    pub fn GetSenderHandle(self: Spout) spoutc.HANDLE {
        return spoutc.GetSenderHandle(self.handle);
    }

    // Received sender texture
    // ID3D11Texture2D* GetSenderTexture(SPOUTHANDLE handle);
    pub fn GetSenderTexture(self: Spout) [*c]spoutc.ID3D11Texture2D {
        return spoutc.GetSenderTexture(self.handle);
    }

    // Received sender sharing mode
    // bool GetSenderCPU(SPOUTHANDLE handle);
    pub fn GetSenderCPU(self: Spout) bool {
        return spoutc.GetSenderCPU(self.handle);
    }

    // Received sender GL/DX compatibility
    // bool GetSenderGLDX(SPOUTHANDLE handle);
    pub fn GetSenderGLDX(self: Spout) bool {
        return spoutc.GetSenderGLDX(self.handle);
    }

    // The path of the host that produced the sender
    // bool GetHostPath(SPOUTHANDLE handle, const char* sendername, char* hostpath, int maxchars);
    pub fn GetHostPath(self: Spout, sender_name: [:0]const u8, host_path: []u8) bool {
        return spoutc.GetHostPath(self.handle, sender_name, host_path);
    }

    // Open sender selection dialog
    // void SelectSender(SPOUTHANDLE handle);
    pub fn SelectSender(self: Spout) void {
        spoutc.SelectSender(self.handle);
    }

    //
    // Frame count
    //

    // Enable or disable frame counting globally
    // void SetFrameCount(SPOUTHANDLE handle, bool bEnable);
    pub fn SetFrameCount(self: Spout, bEnable: bool) void {
        spoutc.SetFrameCount(self.handle, bEnable);
    }

    // Disable frame counting specifically for this application
    // void DisableFrameCount(SPOUTHANDLE handle);
    pub fn DisableFrameCount(self: Spout) void {
        spoutc.DisableFrameCount(self.handle);
    }

    // Return frame count status
    // bool IsFrameCountEnabled(SPOUTHANDLE handle);
    pub fn IsFrameCountEnabled(self: Spout) bool {
        return spoutc.IsFrameCountEnabled(self.handle);
    }

    // Sender frame rate control
    // void HoldFps(SPOUTHANDLE handle, int fps);
    pub fn HoldFps(self: Spout, fps: c_int) void {
        spoutc.HoldFps(self.handle, fps);
    }

    // Get system refresh rate
    // double GetRefreshRate(SPOUTHANDLE handle);
    pub fn GetRefreshRate(self: Spout) f64 {
        return spoutc.GetRefreshRate(self.handle);
    }

    // Signal sync event
    // void SetFrameSync(SPOUTHANDLE handle, const char* SenderName);
    pub fn SetFrameSync(self: Spout, sender_name: [:0]const u8) void {
        spoutc.SetFrameSync(self.handle, sender_name);
    }

    // Wait or test for a sync event
    //   (default: dwTimeout = 0)
    // bool WaitFrameSync(SPOUTHANDLE handle, const char *SenderName, DWORD dwTimeout);
    pub fn WaitFrameSync(self: Spout, sender_name: [:0]const u8, dwTimeout: spoutc.DWORD) bool {
        return spoutc.WaitFrameSync(self.handle, sender_name, dwTimeout);
    }

    // Enable / disable frame sync
    //   (default: bSync = true)
    // void EnableFrameSync(SPOUTHANDLE handle, bool bSync);
    pub fn EnableFrameSync(self: Spout, bSync: bool) void {
        spoutc.EnableFrameSync(self.handle, bSync);
    }

    // Vertical sync status
    // int GetVerticalSync(SPOUTHANDLE handle);
    pub fn GetVerticalSync(self: Spout) c_int {
        return spoutc.GetVerticalSync(self.handle);
    }
    // Lock to monitor vertical sync
    //   (default: bSync = true)
    // bool SetVerticalSync(SPOUTHANDLE handle, bool bSync);
    pub fn SetVerticalSync(self: Spout, bSync: bool) bool {
        return spoutc.SetVerticalSync(self.handle, bSync);
    }

    //
    // Data sharing
    //

    // Write data
    // bool WriteMemoryBuffer(SPOUTHANDLE handle, const char *sendername, const char* data, int length);
    pub fn WriteMemoryBuffer(self: Spout, sender_name: [:0]const u8, data: []const u8, length: c_int) bool {
        return spoutc.WriteMemoryBuffer(self.handle, sender_name, data, length);
    }

    // Read data
    // int  ReadMemoryBuffer(SPOUTHANDLE handle, const char* sendername, char* data, int maxlength);
    pub fn ReadMemoryBuffer(self: Spout, sender_name: [:0]const u8, data: []u8, maxchars: c_int) c_int {
        return spoutc.ReadMemoryBuffer(self.handle, sender_name, data, maxchars);
    }

    // Create a shared memory buffer
    // bool CreateMemoryBuffer(SPOUTHANDLE handle, const char *name, int length);
    pub fn CreateMemoryBuffer(self: Spout, name: [:0]const u8, length: c_int) bool {
        return spoutc.CreateMemoryBuffer(self.handle, name, length);
    }

    // Delete a shared memory buffer
    // bool DeleteMemoryBuffer(SPOUTHANDLE handle);
    pub fn DeleteMemoryBuffer(self: Spout, name: [:0]const u8) bool {
        return spoutc.DeleteMemoryBuffer(self.handle, name);
    }

    // Get the number of bytes available for data transfer
    // int GetMemoryBufferSize(SPOUTHANDLE handle, const char *name);
    pub fn GetMemoryBufferSize(self: Spout, name: [:0]const u8) c_int {
        return spoutc.GetMemoryBufferSize(self.handle, name);
    }

    //
    // Log utilities
    //

    // Open console for debugging
    // void OpenSpoutConsole(SPOUTHANDLE handle);
    pub fn OpenSpoutConsole(self: Spout) void {
        spoutc.OpenSpoutConsole(self.handle);
    }

    // Close console
    //   (default: bWarning = false)
    // void CloseSpoutConsole(SPOUTHANDLE handle, bool bWarning);
    pub fn CloseSpoutConsole(self: Spout, bWarning: bool) void {
        spoutc.CloseSpoutConsole(self.handle, bWarning);
    }

    // Enable spout log to the console
    // void EnableSpoutLog(SPOUTHANDLE handle);
    pub fn EnableSpoutLog(self: Spout) void {
        spoutc.EnableSpoutLog(self.handle);
    }

    // Enable spout log to a file with optional append
    //   (default: bappend = false)
    // void EnableSpoutLogFile(SPOUTHANDLE handle, const char* filename, bool bappend);
    pub fn EnableSpoutLogFile(self: Spout, filename: [:0]const u8, bAppend: bool) void {
        spoutc.EnableSpoutLogFile(self.handle, filename, bAppend);
    }

    // Show the log file folder in Windows Explorer
    // void ShowSpoutLogs(SPOUTHANDLE handle);
    pub fn ShowSpoutLogs(self: Spout) void {
        spoutc.ShowSpoutLogs(self.handle);
    }

    // Disable logging
    // void DisableSpoutLog(SPOUTHANDLE handle);
    pub fn DisableSpoutLog(self: Spout) void {
        spoutc.DisableSpoutLog(self.handle);
    }

    // Set the current log level
    // SPOUT_LOG_SILENT  - Disable all messages
    // SPOUT_LOG_VERBOSE - Show all messages
    // SPOUT_LOG_NOTICE  - Show information messages - default
    // SPOUT_LOG_WARNING - Something might go wrong
    // SPOUT_LOG_ERROR   - Something did go wrong
    // SPOUT_LOG_FATAL   - Something bad happened
    // void SetSpoutLogLevel(SPOUTHANDLE handle, enum SpoutLibLogLevel level);
    pub fn SetSpoutLogLevel(self: Spout, level: spoutc.SpoutLibLogLevel) void {
        spoutc.SetSpoutLogLevel(self.handle, level);
    }

    // General purpose log
    // void SpoutLog(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLog(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLog(self.handle, format, args);
    }

    // Verbose - show log for SPOUT_LOG_VERBOSE or above
    // void SpoutLogVerbose(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLogVerbose(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLogVerbose(self.handle, format, args);
    }

    // Notice - show log for SPOUT_LOG_NOTICE or above
    // void SpoutLogNotice(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLogNotice(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLogNotice(self.handle, format, args);
    }

    // Warning - show log for SPOUT_LOG_WARNING or above
    // void SpoutLogWarning(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLogWarning(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLogWarning(self.handle, format, args);
    }

    // Error - show log for SPOUT_LOG_ERROR or above
    // void SpoutLogError(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLogError(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLogError(self.handle, format, args);
    }

    // Fatal - always show log
    // void SpoutLogFatal(SPOUTHANDLE handle, const char* format, ...);
    pub fn SpoutLogFatal(self: Spout, format: [:0]const u8, args: anytype) void {
        spoutc.SpoutLogFatal(self.handle, format, args);
    }

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
    // bool ReadDwordFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD *pValue);
    pub fn ReadDwordFromRegistry(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8, valuename: [:0]const u8, pValue: spoutc.DWORD) bool {
        return spoutc.ReadDwordFromRegistry(self.handle, hKey, subkey, valuename, pValue);
    }

    // Write subkey DWORD value
    // bool WriteDwordToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, DWORD dwValue);
    pub fn WriteDwordToRegistry(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8, valuename: [:0]const u8, dwValue: spoutc.DWORD) bool {
        return spoutc.WriteDwordToRegistry(self.handle, hKey, subkey, valuename, dwValue);
    }

    // Read subkey character string
    // bool ReadPathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, char *filepath);
    pub fn ReadPathFromRegistry(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8, valuename: [:0]const u8, filepath: []u8) bool {
        return spoutc.ReadPathFromRegistry(self.handle, hKey, subkey, valuename, filepath);
    }

    // Write subkey character string
    // bool WritePathToRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename, const char *filepath);
    pub fn WritePathToRegistry(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8, valuename: [:0]const u8, filepath: [:0]const u8) bool {
        return spoutc.WritePathToRegistry(self.handle, hKey, subkey, valuename, filepath);
    }

    // Remove subkey value name
    // bool RemovePathFromRegistry(SPOUTHANDLE handle, HKEY hKey, const char *subkey, const char *valuename);
    pub fn RemovePathFromRegistry(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8, valuename: [:0]const u8) bool {
        return spoutc.RemovePathFromRegistry(self.handle, hKey, subkey, valuename);
    }

    // Delete a subkey and its values.
    //   It must be a subkey of the key that hKey identifies, but it cannot have subkeys.
    //   Note that key names are not case sensitive.
    // bool RemoveSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey);
    pub fn RemoveSubKey(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8) bool {
        return spoutc.RemoveSubKey(self.handle, hKey, subkey);
    }

    // Find subkey
    // bool FindSubKey(SPOUTHANDLE handle, HKEY hKey, const char *subkey);
    pub fn FindSubKey(self: Spout, hKey: spoutc.HKEY, subkey: [:0]const u8) bool {
        return spoutc.FindSubKey(self.handle, hKey, subkey);
    }

    ////
    //// Information
    ////
    //// Get SDK version number string e.g. "2.007.000"
    //std::string GetSDKversion(SPOUTHANDLE handle);
    //// Computer type
    //bool IsLaptop(SPOUTHANDLE handle);
    // Get the module handle of an executable or dll
    // HMODULE GetCurrentModule(SPOUTHANDLE handle);
    pub fn GetCurrentModule(self: Spout) spoutc.HMODULE {
        return spoutc.GetCurrentModule(self.handle);
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
    // void StartTiming(SPOUTHANDLE handle);
    pub fn StartTiming(self: Spout) void {
        spoutc.StartTiming(self.handle);
    }

    // double EndTiming(SPOUTHANDLE handle);
    pub fn EndTiming(self: Spout) f64 {
        return spoutc.EndTiming(self.handle);
    }

    // -----------------------------------------

    // Initialization status
    // bool IsInitialized(SPOUTHANDLE handle);
    pub fn IsInitialized(self: Spout) bool {
        return spoutc.IsInitialized(self.handle);
    }

    // Bind OpenGL shared texture
    // bool BindSharedTexture(SPOUTHANDLE handle);
    pub fn BindSharedTexture(self: Spout) bool {
        return spoutc.BindSharedTexture(self.handle);
    }

    // Un-bind OpenGL shared texture
    // bool UnBindSharedTexture(SPOUTHANDLE handle);
    pub fn UnBindSharedTexture(self: Spout) bool {
        return spoutc.UnBindSharedTexture(self.handle);
    }

    // OpenGL shared texture ID
    // GLuint GetSharedTextureID(SPOUTHANDLE handle);
    pub fn GetSharedTextureID(self: Spout) spoutc.GLuint {
        return spoutc.GetSharedTextureID(self.handle);
    }

    //
    // Sender names
    //

    // Number of senders
    // int GetSenderCount(SPOUTHANDLE handle);
    pub fn GetSenderCount(self: Spout) c_int {
        return spoutc.GetSenderCount(self.handle);
    }

    // Sender item name
    //   (default: MaxSize = 256)
    // bool GetSender(SPOUTHANDLE handle, int index, char* sendername, int MaxSize);
    pub fn GetSender(self: Spout, index: c_int, sender_name: []u8, max_size: c_int) bool {
        return spoutc.GetSender(self.handle, index, sender_name, max_size);
    }

    // Find a sender in the list
    // bool FindSenderName(SPOUTHANDLE handle, const char* sendername);
    pub fn FindSenderName(self: Spout, sender_name: [:0]const u8) bool {
        return spoutc.FindSenderName(self.handle, sender_name);
    }

    // Sender information
    //bool GetSenderInfo(SPOUTHANDLE handle, const char* sendername, unsigned int &width, unsigned int &height, HANDLE &dxShareHandle, DWORD &dwFormat);
    // Current active sender
    // bool GetActiveSender(SPOUTHANDLE handle, char* Sendername);
    pub fn GetActiveSender(self: Spout, sender_name: []u8, maxchars: c_int) bool {
        return spoutc.GetActiveSender(self.handle, sender_name, maxchars);
    }

    // Set sender as active
    // bool SetActiveSender(SPOUTHANDLE handle, const char* Sendername);
    pub fn SetActiveSender(self: Spout, sender_name: [:0]const u8) bool {
        return spoutc.SetActiveSender(self.handle, sender_name);
    }

    //
    // Get user registry settings recorded by "SpoutSettings"
    // Set them either to the registry or for the application only
    //

    // Get user buffering mode
    // bool GetBufferMode(SPOUTHANDLE handle);
    pub fn GetBufferMode(self: Spout) bool {
        return spoutc.GetBufferMode(self.handle);
    }

    // Set application buffering mode
    //   (default: bActive = true)
    // void SetBufferMode(SPOUTHANDLE handle, bool bActive);
    pub fn SetBufferMode(self: Spout, bActive: bool) void {
        spoutc.SetBufferMode(self.handle, bActive);
    }

    // Get user number of pixel buffers
    // int GetBuffers(SPOUTHANDLE handle);
    pub fn GetBuffers(self: Spout) c_int {
        return spoutc.GetBuffers(self.handle);
    }

    // Set application number of pixel buffers
    // void SetBuffers(SPOUTHANDLE handle, int nBuffers);
    pub fn SetBuffers(self: Spout, nBuffers: c_int) void {
        spoutc.SetBuffers(self.handle, nBuffers);
    }

    // Get user Maximum senders allowed
    // int GetMaxSenders(SPOUTHANDLE handle);
    pub fn GetMaxSenders(self: Spout) c_int {
        return spoutc.GetMaxSenders(self.handle);
    }

    // Set user Maximum senders allowed
    // void SetMaxSenders(SPOUTHANDLE handle, int maxSenders);
    pub fn SetMaxSenders(self: Spout, maxSenders: c_int) void {
        spoutc.SetMaxSenders(self.handle, maxSenders);
    }

    //
    // Graphics compatibility
    //

    // Get auto GPU/CPU share depending on compatibility
    // bool GetAutoShare(SPOUTHANDLE handle);
    pub fn GetAutoShare(self: Spout) bool {
        return spoutc.GetAutoShare(self.handle);
    }

    // Set auto GPU/CPU share depending on compatibility
    //   (default: bAuto = true)
    // void SetAutoShare(SPOUTHANDLE handle, bool bAuto);
    pub fn SetAutoShare(self: Spout, bAuto: bool) void {
        spoutc.SetAutoShare(self.handle, bAuto);
    }

    // OpenGL texture share compatibility
    // bool IsGLDXready(SPOUTHANDLE handle);
    pub fn IsGLDXready(self: Spout) bool {
        return spoutc.IsGLDXready(self.handle);
    }

    //
    // Adapter functions
    //

    // The number of graphics adapters in the system
    // int GetNumAdapters(SPOUTHANDLE handle);
    pub fn GetNumAdapters(self: Spout) c_int {
        return spoutc.GetNumAdapters(self.handle);
    }

    // Adapter item name
    // bool GetAdapterName(SPOUTHANDLE handle, int index, char *adaptername, int maxchars);
    pub fn GetAdapterName(self: Spout, index: c_int, adapter_name: []u8, maxchars: c_int) bool {
        return spoutc.GetAdapterName(self.handle, index, adapter_name, maxchars);
    }
    // Return current adapter name
    // char * AdapterName(SPOUTHANDLE handle);
    pub fn AdapterName(self: Spout) [:0]const u8 {
        return spoutc.AdapterName(self.handle);
    }

    // Get adapter index
    // int GetAdapter(SPOUTHANDLE handle);
    pub fn GetAdapter(self: Spout) c_int {
        return spoutc.GetAdapter(self.handle);
    }

    //
    // Graphics preference
    //
    // Windows 10+ SDK required
    //#ifdef NTDDI_WIN10_RS4

    // Get the Windows graphics preference for an application
    // -1 - Not registered
    //  0 - Let Windows decide  DXGI_GPU_PREFERENCE_UNSPECIFIED
    //  1 - Power saving        DXGI_GPU_PREFERENCE_MINIMUM_POWER
    //  2 - High performance    DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE
    // int GetPerformancePreference(SPOUTHANDLE handle, const char* path);
    pub fn GetPerformancePreference(self: Spout, path: [:0]const u8) c_int {
        return spoutc.GetPerformancePreference(self.handle, path);
    }

    // Set the Windows graphics preference for an application
    // bool SetPerformancePreference(SPOUTHANDLE handle, int preference, const char* path);
    pub fn SetPerformancePreference(self: Spout, preference: c_int, path: [:0]const u8) bool {
        return spoutc.SetPerformancePreference(self.handle, preference, path);
    }

    // Get the graphics adapter name for a Windows preference
    // bool GetPreferredAdapterName(SPOUTHANDLE handle, int preference, char* adaptername, int maxchars);
    pub fn GetPreferredAdapterName(self: Spout, preference: c_int, adapter_name: []u8, maxchars: c_int) bool {
        return spoutc.GetPreferredAdapterName(self.handle, preference, adapter_name, maxchars);
    }

    // Set graphics adapter index for a Windows preference
    // bool SetPreferredAdapter(SPOUTHANDLE handle, int preference);
    pub fn SetPreferredAdapter(self: Spout, preference: c_int) bool {
        return spoutc.SetPreferredAdapter(self.handle, preference);
    }

    // Availability of Windows graphics preference
    // bool IsPreferenceAvailable(SPOUTHANDLE handle);
    pub fn IsPreferenceAvailable(self: Spout) bool {
        return spoutc.IsPreferenceAvailable(self.handle);
    }
    // Is the path a valid application
    // bool IsApplicationPath(SPOUTHANDLE handle, const char* path);
    pub fn IsApplicationPath(self: Spout, path: [:0]const u8) bool {
        return spoutc.IsApplicationPath(self.handle, path);
    }

    //
    // OpenGL utilities
    //

    // Create an OpenGL window and context for situations where there is none.
    //   Not used if applications already have an OpenGL context.
    //   Always call CloseOpenGL afterwards.
    // bool CreateOpenGL(SPOUTHANDLE handle);
    pub fn CreateOpenGL(self: Spout) bool {
        return spoutc.CreateOpenGL(self.handle);
    }

    // Close OpenGL window
    // bool CloseOpenGL(SPOUTHANDLE handle);
    pub fn CloseOpenGL(self: Spout) bool {
        return spoutc.CloseOpenGL(self.handle);
    }

    // Copy OpenGL texture with optional invert
    //   (default: bInvert = false, HostFBO = 0)
    //   Textures must be the same size
    // bool CopyTexture(SPOUTHANDLE handle, GLuint SourceID, GLuint SourceTarget,
    // GLuint DestID, GLuint DestTarget,
    // unsigned int width, unsigned int height,
    // bool bInvert, GLuint HostFBO);
    pub fn CopyTexture(self: Spout, sourceID: spoutc.GLuint, sourceTarget: spoutc.GLuint, destID: spoutc.GLuint, destTarget: spoutc.GLuint, width: c_uint, height: c_uint, bInvert: bool, hostFbo: spoutc.GLuint) bool {
        return spoutc.CopyTexture(self.handle, sourceID, sourceTarget, destID, destTarget, width, height, bInvert, hostFbo);
    }

    //
    // Formats
    //

    // Get sender DX11 shared texture format
    // DXGI_FORMAT GetDX11format(SPOUTHANDLE handle);
    pub fn GetDX11format(self: Spout) spoutc.DXGI_FORMAT {
        return spoutc.GetDX11format(self.handle);
    }

    // Set sender DX11 shared texture format
    // void SetDX11format(SPOUTHANDLE handle, DXGI_FORMAT textureformat);
    pub fn SetDX11format(self: Spout, textureformat: spoutc.DXGI_FORMAT) void {
        spoutc.SetDX11format(self.handle, textureformat);
    }

    // Return OpenGL compatible DX11 format
    // DXGI_FORMAT DX11format(SPOUTHANDLE handle, GLint glformat);
    pub fn DX11format(self: Spout, glformat: spoutc.GLint) spoutc.DXGI_FORMAT {
        return spoutc.DX11format(self.handle, glformat);
    }

    // Return DX11 compatible OpenGL format
    //   (default: textureformat = DXGI_FORMAT_UNKNOWN)
    // GLint GLDXformat(SPOUTHANDLE handle, DXGI_FORMAT textureformat);
    pub fn GLDXformat(self: Spout, textureformat: spoutc.DXGI_FORMAT) spoutc.GLint {
        return spoutc.GLDXformat(self.handle, textureformat);
    }

    // Return OpenGL texture internal format
    // int GLformat(SPOUTHANDLE handle, GLuint TextureID, GLuint TextureTarget);
    pub fn GLformat(self: Spout, textureID: spoutc.GLuint, textureTarget: spoutc.GLuint) c_int {
        return spoutc.GLformat(self.handle, textureID, textureTarget);
    }

    //// Return OpenGL texture format description
    //std::string GLformatName(SPOUTHANDLE handle, GLint glformat = 0);

    //
    // DirectX utilities
    //

    // bool OpenDirectX(SPOUTHANDLE handle);
    pub fn OpenDirectX(self: Spout) bool {
        return spoutc.OpenDirectX(self.handle);
    }

    // void CloseDirectX(SPOUTHANDLE handle);
    pub fn CloseDirectX(self: Spout) void {
        spoutc.CloseDirectX(self.handle);
    }

    // Initialize and prepare DirectX 11
    //    (default: pDevice = NULL)
    // bool OpenDirectX11(SPOUTHANDLE handle, void * pDevice);
    pub fn OpenDirectX11(self: Spout, pDevice: ?*anyopaque) bool {
        return spoutc.OpenDirectX11(self.handle, pDevice);
    }

    // void CloseDirectX11(SPOUTHANDLE handle);
    pub fn CloseDirectX11(self: Spout) void {
        spoutc.CloseDirectX11(self.handle);
    }

    // Return the class device
    // void* GetDX11Device(SPOUTHANDLE handle);
    pub fn GetDX11Device(self: Spout) ?*anyopaque {
        return spoutc.GetDX11Device(self.handle);
    }

    // Return the class context
    // void* GetDX11Context(SPOUTHANDLE handle);
    pub fn GetDX11Context(self: Spout) ?*anyopaque {
        return spoutc.GetDX11Context(self.handle);
    }

    // Library release function
    // void Release(SPOUTHANDLE handle);
    pub fn Release(self: Spout) void {
        spoutc.Release(self.handle);
    }
};
