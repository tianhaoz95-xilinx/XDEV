import subprocess
import parse
import os
import ftype

class cppLinter():
    def __init__(self):
        self.results = []
        self.sorted_results = []
        self.total = 0
        self.lint = 0
        self.invalid = 0

    def lint_dir(self, root_dir, filters):
        dir_total = 0
        dir_lint = 0
        dir_invalid = 0
        for root, dirs, files in os.walk(root_dir):
            dir_total += len(files)
            for f in files:
                if ftype.filter_files(filters, f):
                    target_filename = os.path.join(root, f)
                    try:
                        result = self.lint_one(target_filename)
                        result['id'] = f
                        self.results.append(result)
                        dir_lint += 1
                    except:
                        dir_invalid += 1
        self.total += dir_total
        self.lint += dir_lint
        self.invalid += dir_invalid
        print('Done linting ' + root_dir + ': ' + str(dir_lint) + ' / ' + str(dir_total) + ' linted' + ', invalid: ' + str(dir_invalid))

    def lint_one(self, filename):
        p = subprocess.Popen(['python', '-m', 'cpplint', filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = p.stderr.read()
        parsed_output = parse.parse_linter_output(output)
        return parsed_output

    def finalize(self):
        self.sorted_results = sorted(self.results, key=lambda x: x['count'], reverse=True)

    def get_top(self, cnt):
        bound = min(cnt, len(self.sorted_results))
        return self.sorted_results[:bound]