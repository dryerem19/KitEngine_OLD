import yaml # for read/write .yaml config
import sys  # for read command prompt args
import os   # for create symlink

from elevate import elevate # for check admin privilegies

elevate()

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
    resources_lynk: str = f"{cmake_output_path}/res"
    try:
        if not os.path.isdir(resources_lynk) or not os.path.islink(resources_lynk):
            os.symlink(f"{cmake_source_path}/res", resources_lynk)
    except OSError as e:
        error_code = e.winerror
        if sys.platform != "win32":
            error_code = e.errno
        print(f"[POST-BUILD-ERROR] - Cannot create symlink to resources folder, error code({e.errno})")
        exit(-1)
    else:
        print("[POST-BUILD-ERROR] - Successfully create symlink to resources folder")

with open(path_to_build_fileinfo, "w") as file:
    yaml.dump(data, file)

create_resources_symlink()
increment_build_number()