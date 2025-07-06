const std = @import("std");

const version: std.SemanticVersion = .{ .major = 2, .minor = 13, .patch = 5 };

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const linkage = b.option(std.builtin.LinkMode, "linkage", "Link mode") orelse .static;
    //const strip = b.option(bool, "strip", "Omit debug information");
    //const pic = b.option(bool, "pie", "Produce Position Independent Code");

    const lib_spout = buildSpout(b, target, optimize, linkage);

    const main_mod = b.createModule(.{
        .root_source_file = b.path("src/root.zig"),
        .target = target,
        .optimize = optimize,
    });
    main_mod.linkLibrary(lib_spout);
    main_mod.addIncludePath(b.path("src"));
    const main_lib = b.addLibrary(.{
        .linkage = linkage,
        .name = "spout",
        .root_module = main_mod,
    });
    b.installArtifact(main_lib);

    const test_step = b.step("test", "Run unit tests");

    const unit_tests = b.addTest(.{
        .root_module = main_mod,
        .link_libcpp = true,
        .link_libc = true,
    });

    const run_unit_tests = b.addRunArtifact(unit_tests);
    test_step.dependOn(&run_unit_tests.step);
}

fn buildSpout(b: *std.Build, target: std.Build.ResolvedTarget, optimize: std.builtin.OptimizeMode, linkage: std.builtin.LinkMode) *std.Build.Step.Compile {
    const spout_dep = b.dependency("spout", .{});
    const mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });
    for (spout_link_libs) |lib| {
        mod.linkSystemLibrary(lib, .{
            .preferred_link_mode = .dynamic,
            .needed = true,
        });
    }
    mod.addIncludePath(spout_dep.path("SPOUTSDK/SpoutLibrary"));
    mod.addCSourceFiles(.{
        .root = spout_dep.path("SPOUTSDK/SpoutGL"),
        .files = spout_gl_src,
    });
    mod.addCSourceFiles(.{
        .root = spout_dep.path("SPOUTSDK/SpoutLibrary"),
        .files = spout_library_src,
    });
    mod.addCSourceFile(.{
        .file = b.path("src/SpoutC.cpp"),
    });
    const lib = b.addLibrary(.{
        .name = "spout",
        .linkage = linkage,
        .root_module = mod,
    });
    lib.installHeader(b.path("src/SpoutC.h"), "SpoutC.h");
    return lib;
}

pub const spout_library_src: []const []const u8 = &.{
    "SpoutLibrary.cpp",
};

pub const spout_gl_src: []const []const u8 = &.{
    "Spout.cpp",
    "SpoutCopy.cpp",
    "SpoutDirectX.cpp",
    "SpoutFrameCount.cpp",
    "SpoutGL.cpp",
    "SpoutGLextensions.cpp",
    "SpoutReceiver.cpp",
    "SpoutSender.cpp",
    "SpoutSenderNames.cpp",
    "SpoutSharedMemory.cpp",
    "spoutUtils.cpp",
};

pub const spout_link_libs: []const []const u8 = &.{ "opengl32", "kernel32", "user32", "gdi32", "winspool", "comdlg32", "comctl32", "advapi32", "shell32", "ole32", "oleaut32", "uuid", "odbc32", "odbccp32", "d3d9", "d3d11", "DXGI", "version", "winmm" };

const FLAGS = [_][]const u8{ "-std=c++20", "-msse4" };
