from github import Github

g = Github("xxx", "xxx")
g = Github("xxx")

repo = g.get_repo("tianhaoz95-xilinx/XDEV")
repo.create_issue(title="This is a new issue", body="This is the issue body")