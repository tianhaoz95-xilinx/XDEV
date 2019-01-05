import config

def compose_title(lint_result):
    title = 'Lint result for ' + lint_result['id']
    return title

def compose_body(lint_result):
    project_root = config.get_project_root()
    clean_outputs = []
    for output in lint_result['output']:
        clean_output = output.replace(':', '#L', 1) \
                            .replace(':', '\n\n```cpp\n', 1) \
                            .replace(project_root, 'https://github.com/tianhaoz95-xilinx/XDEV/blob/master')
        clean_output = clean_output + '\n```\n\n'
        clean_outputs.append(clean_output)
    body = '\n'.join('- [ ] Mark after resolved\n' + output for output in clean_outputs)
    body = '## Issues\n' + body
    body = '# Found ' + str(lint_result['count']) + ' issues\n' + body
    return body