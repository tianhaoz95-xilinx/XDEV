def parse_command_input(command_input):
    arguments = command_input.strip().split(' ')
    argument_type = arguments[0]
    argument_payload = arguments[1:]
    return argument_type, argument_payload