# Spout

This is [Spout](https://github.com/leadedge/Spout2), packaged for [Zig](https://ziglang.org/).

## Installation

First, update your `build.zig.zon`:

```
# Initialize a `zig build` project if you haven't already
zig init
zig fetch --save git+https://github.com/Lucurious/ZigSpout2.git
```

You can then import `spout` in your `build.zig` with:

```zig
const spout_dependency = b.dependency("spout", .{
    .target = target,
    .optimize = optimize,
});
your_exe.linkLibrary(spout_dependency.artifact("spout"));
```