import sys
import os
import re
from typing import Sequence

if len(sys.argv) < 2:
    print(f'Usage: {sys.argv[0]} <project name>')
    sys.exit(-1)

project_name = sys.argv[1].lower()
project_name_upper = project_name.upper()

if not re.match(r'[a-zA-Z]+[\w_-]*', project_name):
    print(f'Invalid project name: {project_name}')
    sys.exit(-1)


def replace_file_content(filepath: str, old_new_pairs: Sequence[tuple[str, str]]):
    with open(filepath, 'r') as f:
        content = f.read()
        for old, new in old_new_pairs:
            content = content.replace(old, new)
    with open(filepath, 'w') as f:
        f.write(content)


# modify mylib_version.h.in
replace_file_content('mylib_version.h.in', [
                     ('MYLIB', project_name_upper), ('mylib', project_name)])
os.rename('mylib_version.h.in', f'{project_name}_version.h.in')

# modify mylib_config.h.in
replace_file_content('mylib_config.h.in', [('MYLIB', project_name_upper)])
os.rename('mylib_config.h.in', f'{project_name}_config.h.in')

# modify CMakeLists.txt
replace_file_content('CMakeLists.txt', [('mylib', project_name)])

# modify include/mylib/mylib_api.h
replace_file_content('include/mylib/mylib_api.h',
                     [('MYLIB', project_name_upper)])
os.rename('include/mylib/mylib_api.h', f'include/mylib/{project_name}_api.h')

# modify include/mylib/mylib.h
replace_file_content('include/mylib/mylib.h',
                     [('MYLIB', project_name_upper), ('mylib', project_name)])
os.rename('include/mylib/mylib.h', f'include/mylib/{project_name}.h')

# modify include/mylib/mylib.hpp
replace_file_content('include/mylib/mylib.hpp',
                     [('MYLIB', project_name_upper), ('mylib', project_name)])
os.rename('include/mylib/mylib.hpp', f'include/mylib/{project_name}.hpp')

# rename include/mylib
os.rename('include/mylib', f'include/{project_name}')

# modify src/internal.h
replace_file_content('src/internal.h', [('MYLIB', project_name_upper)])

# modify src/mylib.cpp
replace_file_content('src/mylib.cpp', [('mylib', project_name)])
os.rename('src/mylib.cpp', f'src/{project_name}.cpp')

# modify tests/CMakeLists.txt
replace_file_content('tests/CMakeLists.txt', [('mylib', project_name)])

# modify tests/test_mylib.cpp
replace_file_content('tests/test_mylib.cpp',
                     [('MYLIB', project_name_upper), ('mylib', project_name)])
os.rename('tests/test_mylib.cpp', f'tests/test_{project_name}.cpp')

# modify mylib.CLR/AssemblyInfo.cpp.in
replace_file_content('mylib.CLR/AssemblyInfo.cpp.in',
                     [('mylib', project_name)])

# modify mylib.CLR/CMakeLists.txt
replace_file_content('mylib.CLR/CMakeLists.txt', [('mylib', project_name)])

# modify mylib.CLR/mylib.clr.cpp
replace_file_content('mylib.CLR/mylib.clr.cpp', [('mylib', project_name)])
os.rename('mylib.CLR/mylib.clr.cpp', f'mylib.CLR/{project_name}.clr.cpp')

# modify mylib.CLR/mylib.clr.h
replace_file_content('mylib.CLR/mylib.clr.h', [('mylib', project_name)])
os.rename('mylib.CLR/mylib.clr.h', f'mylib.CLR/{project_name}.clr.h')

# rename mylib.CLR
os.rename('mylib.CLR', f'{project_name}.CLR')
