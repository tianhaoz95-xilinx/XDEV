import subprocess
import os
import re
import ftype
import config
import linter
import gitbot

def main():
    cpplinter = linter.cppLinter()
    lint_roots = config.get_lint_roots()
    for lint_root in lint_roots:
        cpplinter.lint_dir(lint_root, config.get_file_filters())
    cpplinter.finalize()
    top_results = cpplinter.get_top(5)
    bot = gitbot.GitBot()
    bot.post_lint_issues(top_results)

if __name__ == '__main__':
    main()