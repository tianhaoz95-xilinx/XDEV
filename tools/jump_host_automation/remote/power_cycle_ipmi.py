import pyipmi
import pyipmi.interfaces

def main():
    interface = pyipmi.interfaces.create_interface('ipmitool', interface_type='lan')
    connection = pyipmi.create_connection(interface)
    connection.target = pyipmi.Target(0x82)
    connection.target.set_routing([(0x81,0x20,0),(0x20,0x82,7)])
    connection.session.set_session_type_rmcp('10.23.53.114', port=623)
    connection.session.set_auth_type_user('ADMIN', 'ADMIN')
    connection.session.establish()
    print(connection.get_device_id())

if __name__ == '__main__':
    main()