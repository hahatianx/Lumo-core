HEADFILES = ./include 
BUILD_DIR = ./build
OBJ_DIR = ./build/obj

CC = gcc

# COMPONENT

$(OBJ_DIR)/queue.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/queue.o util/queue.c

$(OBJ_DIR)/unix_cp_queue.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/unix_cp_queue.o util/cp_queue.c

$(OBJ_DIR)/file_io.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/file_io.o io/unix/readwrite.c

$(OBJ_DIR)/socket_unix.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/socket_unix.o network/unix/socket.c

$(OBJ_DIR)/message_send.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/message_send.o network/unix/message_send.c

$(OBJ_DIR)/message.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/message.o network/message.c

$(OBJ_DIR)/thread.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/thread.o thread/unix/thread.c

$(OBJ_DIR)/sender_thrd.o:
	$(CC) -c -I$(HEADFILES) -o $(OBJ_DIR)/sender_thrd.o thread/unix/msend_thread.c


# MODULE

SENDER_THRD_MODULE := sender_thrd.o thread.o message.o message_send.o socket_unix.o file_io.o unix_cp_queue.o queue.o

# TESTS

alltest: list_test_lib queue_test_lib message_test message_sender_test cp_queue_test

list_test_lib:
	$(CC) -fPIC -o $(BUILD_DIR)/link_list_test.so -shared -I$(HEADFILES) test/util/link_list_test.c

queue_test_lib:
	$(CC) -fPIC -o $(BUILD_DIR)/queue_test.so -shared -I$(HEADFILES) test/util/queue_test.c util/queue.c

message_test:
	$(CC) -fPIC -o $(BUILD_DIR)/message_test.so -shared -I$(HEADFILES) test/network/message_test.c network/message.c

MESSAGE_SENDER_TEST_OBJ := file_io.o socket_unix.o message_send.o message.o
message_sender_test: $(patsubst %,$(OBJ_DIR)/%,$(MESSAGE_SENDER_TEST_OBJ))
	$(CC) -fPIC -o $(BUILD_DIR)/message_sender_test.so -shared -I$(HEADFILES) test/network/message_sender_test.c $^

CP_QUEUE_TEST_OBJ := unix_cp_queue.o queue.o thread.o
cp_queue_test: $(patsubst %, $(OBJ_DIR)/%, $(CP_QUEUE_TEST_OBJ))
	$(CC) -fPIC -o $(BUILD_DIR)/cp_queue_test.so -shared -I$(HEADFILES) test/util/cp_queue_test.c $^

SENDER_THRD_TEST_OBJ := $(SENDER_THRD_MODULE) 
sender_thrd_test: $(patsubst %, $(OBJ_DIR)/%, $(SENDER_THRD_TEST_OBJ))
	$(CC) -fPIC -o $(BUILD_DIR)/sender_thrd_test.so -shared -I$(HEADFILES) test/thread/msend_thread_test.c $^

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(BUILD_DIR)/*.so