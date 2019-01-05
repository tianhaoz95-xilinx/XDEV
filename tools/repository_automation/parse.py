def parse_linter_output(output):
    output_arr = output.strip().split('\n')
    res = {}
    res['output'] = output_arr[:-2]
    res['count'] = int(output_arr[-1].split(':')[-1])
    return res