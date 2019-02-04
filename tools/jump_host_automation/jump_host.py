from jumpssh import SSHSession

class JumpHost():
    def __init__(self):
        self.machines = {}
        self.host = None
    
    def config(self, hostname, username, password, workstation_id):
        host_session = SSHSession(hostname, username, password=password).open()
        self.host = {
            'id': workstation_id,
            'hostname': hostname,
            'username': username,
            'password': password,
            'session': host_session
        }

    def add(self, hostname, username, password, workstation_id):
        machine_session = self.host['session'].get_remote_session(hostname, username, password=password)
        self.machines[workstation_id] = {
            'id': workstation_id,
            'hostname': hostname,
            'username': username,
            'password': password,
            'session': machine_session
        }

    def check_and_reconnect(self, workstation_id):
        pass

    def get_machine(self, workstation_id):
        if hostname not in self.machines:
            raise RuntimeError(workstation_id + ' not found.')
        self.check_and_reconnect(workstation_id)
        session = self.machines[workstation_id]
        return session

    def get_machine_names(self):
        return self.machines.keys()