def get_user_information(msg, val):
    res = val
    if val == '__ask_user__':
        res = input(msg)
    return res     