import os

def get_file_filters():
    file_filters = [
        '.hpp', 
        '.cpp', 
        '.h',
        '.c',
        '.cc',
        '.cl'
    ]
    return file_filters

def get_lint_roots():
    project_root = get_project_root()
    lint_roots = [
        os.path.join(project_root, 'xdev', 'dev'),
        os.path.join(project_root, 'xdev', 'test', 'xrt'),
        os.path.join(project_root, 'darkside', 'kernel')
    ]
    return lint_roots

def get_project_root():
    file_path = os.path.dirname(os.path.realpath(__file__))
    tool_root = os.path.join(file_path, os.pardir)
    project_root = os.path.abspath(os.path.join(tool_root, os.pardir))
    return project_root
