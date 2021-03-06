from github import Github
import composer
import os

class GitBot():
    def __init__(self):
        token = ""
        if 'GITHUB_ACCOUNT_TOKEN' in os.environ:
            token = os.environ['GITHUB_ACCOUNT_TOKEN']
        else:
            raise RuntimeError('GITHUB_ACCOUNT_TOKEN not found')
        self.github = Github(token)
        self.repo = self.github.get_repo('tianhaoz95-xilinx/XDEV')
        milestones = self.repo.get_milestones()
        milestone_found = False
        for m in milestones:
            if m.title == 'Coding Style Fixing':
                self.milestone = m
                milestone_found = True
        if not milestone_found:
            self.milestone = self.repo.create_milestone(title='Coding Style Fixing')
        print('GitBot init finished')

    def post_lint_issue(self, lint_result):
        title = composer.compose_title(lint_result)
        body = composer.compose_body(lint_result)
        issue = self.find_issue(title)
        if issue is None:
            self.repo.create_issue(title=title, body=body, milestone=self.milestone)
        else:
            issue.edit(title=title, body=body, milestone=self.milestone)

    def post_lint_issues(self, lint_results):
        for lint_result in lint_results:
            self.post_lint_issue(lint_result)
        print('All lint result issues posted')

    def find_issue(self, title):
        issues = self.repo.get_issues()
        for issue in issues:
            if issue.title == title:
                return issue
        return None