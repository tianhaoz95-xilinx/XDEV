def filter_files(filters, filename):
    for f in filters:
        if filename.endswith(f):
            return True
    return False