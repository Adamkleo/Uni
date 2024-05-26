
def readLine(connection) -> str:
    message_total = ''
    while True:
        char = connection.recv(1).decode('utf-8')  # Read one byte
        if char == '\0':  # Stop reading if null terminator is reached
            break
        message_total += char
    return message_total

def readString(connection) -> str:
    parts = []
    while True:
        part = connection.recv(1024)  # Read in chunks of 1024 bytes
        if not part:  # Handle case where socket is closed or recv returns an empty string
            break
        if b'\0' in part:
            parts.append(part[:part.index(b'\0')].decode('utf-8'))
            break
        parts.append(part.decode('utf-8'))
    return ''.join(parts)


def parseUserList(user_list) -> dict:
    lines = user_list.strip().split("\n")
    user_dict = {}
    for line in lines:
        if line.strip():  # Ensure the line is not empty
            username, ip, port = line.split()
            user_dict[username] = (ip, port)
    return user_dict