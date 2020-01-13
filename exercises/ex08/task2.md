# Task 2

## Overall Overview

The chat server example contains 3 files, one of which is a header file (_chat_message_) containing all information about the message, its contents and the length. One containing a class _chat_client_ which creates a client, allows to connect to a server, and enables reading and writing of the messages. [And the last file](https://www.boost.org/doc/libs/1_72_0/doc/html/boost_asio/example/cpp11/chat/chat_server.cpp) _chat_server_ contains multiple classes for the creation of the server and the general process of chatting using this server.

- _chat_participant_
- _chat_room_ where participants can be added or removed and messages can be delivered
- _chat_session_ where participants can join a room and start chatting
- _chat_server_ which accepts a connection and the starts a chat_server

## Session Management

The session management uses shared pointers and **CRTP**. The _chat_session_ inherits from _chat_participant_ and _std::enable_shared_from_this_, where the last of them is specialized using _chat_session_. With _enable_shared_from_this_ we are able to generate new instances of an object that is currently managed by a shared pointer. In the example this shared pointer are the participants as they are saved to a shared pointer and made shared in the main when the _chat_server_ accepts the connection. The use of _shared_from_this_ allows us to return a shared pointer with shared ownership. In our case we create an instance of _chat_session_ when the server accepts the connection, we make the session shared, at the same time a room is created and with the use of _shared_from_this_ a participant is added to this room.
