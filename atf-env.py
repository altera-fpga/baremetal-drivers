import os
import sys

if __name__ == "__main__":
    with open("atf_env.simics", 'w') as f:
        f.write(f"$atf_base_dir={sys.argv[1]}\n")

