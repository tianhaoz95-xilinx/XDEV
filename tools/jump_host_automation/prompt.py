from chatterbot import ChatBot
from chatterbot.trainers import ChatterBotCorpusTrainer
from command import exec_dict
from parse import parse_command_input

class TerminalPrompt():
    def __init__(self):
        print('Initializing the assistant ...')
        self.chatbot = ChatBot('Not IT\'s Friend')
        self.trainer = ChatterBotCorpusTrainer(self.chatbot)
        self.trainer.train("chatterbot.corpus.english")

    def exec_command(self, jump_host):
        prompt_msg = '\n ~(^-^)~ ~(^-^)~ ===>  '
        command_input = input(prompt_msg)
        argument_type, argument_payload = parse_command_input(command_input)
        if argument_type in exec_dict:
            return exec_dict[argument_type](argument_payload, jump_host)
        print('I do recognize this command. Please use the help command to show the documentation.\n')
        print('However, I will answer your question anyway\n')
        print('Thinking ...\n')
        response = self.chatbot.get_response(command_input)
        print(str(response) + '\n')
        return False
