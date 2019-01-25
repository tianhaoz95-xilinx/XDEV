import pyipmi
import pyipmi.interfaces

def main():
    interface = pyipmi.interfaces.create_interface('ipmitool', interface_type='lan')
    connection = pyipmi.create_connection(interface)
    connection.session.set_session_type_rmcp('10.0.0.1')
    connection.session.set_auth_type_user('ADMIN', 'ADMIN')
    connection.session.establish()

if __name__ == '__main__':
    main()