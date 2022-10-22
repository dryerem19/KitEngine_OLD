import subprocess
import yaml
import sys

print("[POST-BUILD] - Started...")
cmake_source_path: str = sys.argv[1]
cmake_output_path: str = sys.argv[2]
path_to_build_fileinfo: str = f"{cmake_source_path}/build.yaml"

print(f"[POST-BUILD] - Cmake source path: {cmake_source_path}")
print(f"[POST-BUILD] - Cmake build path:  {cmake_output_path}")

with open(path_to_build_fileinfo, "r") as file:
    data = yaml.safe_load(file)


def increment_build_number() -> None:
    build_number: int = data['KitEngine']['build']
    build_number += 1

    data['KitEngine']['build'] = build_number
    print(f"[POST-BUILD] - Build number increment from: {build_number - 1} to: {build_number}")


def create_resources_symlink() -> None:

    if sys.platform == "win32":
        subprocess.run(f'mklink /J "{cmake_source_path}/res" "{cmake_output_path}/res"', shell=True)
    elif sys.platform == "linux":
        subprocess.run(f'ln -s {cmake_source_path}/res {cmake_output_path}/res', shell=True)

    print("[POST-BUILD] - Create symlink to resources folder")


increment_build_number()
with open(path_to_build_fileinfo, "w") as file:
    yaml.dump(data, file)

create_resources_symlink()
