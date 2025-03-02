const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});

    const optimize = b.standardOptimizeOption(.{});

    // Add GoogleTest dependency
    const gtest_dep = b.dependency("googletest", .{
        .target = target,
        .optimize = optimize,
    });

    const exe = b.addExecutable(.{
        .name = "bfvm",
        .optimize = optimize,
        .target = target,
    });
    exe.addCSourceFiles(.{
        .files = srcs,
        .flags = &.{
            "-Wall",
            "-Wextra",
            "-std=c++14",
        },
    });
    exe.linkLibCpp();

    b.installArtifact(exe);

    const run_exe = b.addRunArtifact(exe);

    run_exe.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_exe.addArgs(args);
    }

    const run_step = b.step("run", "Run bfvm with a brain fuck file as argument");

    run_step.dependOn(&run_exe.step);

    const test_exe = b.addExecutable(.{
        .name = "bfvm_tests",
        .optimize = optimize,
        .target = target,
    });

    test_exe.addCSourceFiles(.{
        .files = test_srcs,
        .flags = &.{
            "-Wall",
            "-Wextra",
            "-std=c++14",
        },
    });

    test_exe.linkLibCpp();
    test_exe.addCSourceFile(.{
        .file = gtest_dep.path("googletest/src/gtest_main.cc"),
        .flags = &.{},
    });
    test_exe.addIncludePath(gtest_dep.path("googletest/include"));
    test_exe.addIncludePath(gtest_dep.path("googletest"));
    test_exe.installHeadersDirectory(gtest_dep.path("googletest/include"), ".", .{});

    test_exe.linkLibCpp();

    // Add a test step to run the tests
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&test_exe.step);
}

const srcs = &.{
    "src/compiler.cc",
    "src/instruction.cc",
    "src/machine.cc",
    "main.cc",
};

const test_srcs = &.{
    "test/compiler_test.cc",
    "test/machine_test.cc",
};
