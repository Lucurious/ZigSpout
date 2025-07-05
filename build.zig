const std = @import("std");

const version: std.SemanticVersion = .{ .major = 2, .minor = 13, .patch = 5 };

pub fn build(b: *std.Build) void {
    const upstream = b.dependency("spout", .{});
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const linkage = b.option(std.builtin.LinkMode, "linkage", "Link mode") orelse .static;
    const strip = b.option(bool, "strip", "Omit debug information");
    const pic = b.option(bool, "pie", "Produce Position Independent Code");

    const spout_lib = b.addLibrary(.{
        .linkage = linkage,
        .name = "spout",
        .version = version,
        .root_module = b.createModule(.{
            .target = target,
            .optimize = optimize,
            .link_libc = true,
            .link_libcpp = true,
            .strip = strip,
            .pic = pic,
        }),
    });
    b.installArtifact((spout_lib));
    spout_lib.installHeader(upstream.path("SPOUTSDK/SpoutLibrary/SpoutLibrary.h"), "SpoutLibrary/SpoutLibrary.h");
    spout_lib.root_module.addIncludePath(upstream.path("SPOUTSDK"));
    spout_lib.root_module.addCSourceFiles(.{ .files = spout_library_src, .root = upstream.path("SPOUTSDK"), .flags = spout_flags });
    spout_lib.linkSystemLibrary("c++");
}

pub const spout_library_src: []const []const u8 = &.{
    "SpoutLibrary/SpoutLibrary.cpp",
};

pub const spout_flags: []const []const u8 = &.{};
