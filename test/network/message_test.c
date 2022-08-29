#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "test.h"
#include "network/message.h"


void init_message_block(message_t *msg, char *buffer) {
    char *dummy_message = "That can I;\n\
At least, the whisper goes so. Our last king,\n\
Whose image even but now appear'd to us,\n\
Was, as you know, by Fortinbras of Norway,\n\
Thereto prick'd on by a most emulate pride,\n\
Dared to the combat; in which our valiant Hamlet--\n\
For so this side of our known world esteem'd him--\n\
Did slay this Fortinbras; who by a seal'd compact,\n\
Well ratified by law and heraldry,\n\
Did forfeit, with his life, all those his lands\n\
Which he stood seized of, to the conqueror:\n\
Against the which, a moiety competent\n\
Was gaged by our king; which had return'd\n\
To the inheritance of Fortinbras,\n\
Had he been vanquisher; as, by the same covenant,\n\
And carriage of the article design'd,\n\
His fell to Hamlet. Now, sir, young Fortinbras,\n\
Of unimproved mettle hot and full,\n\
Hath in the skirts of Norway here and there\n\
Shark'd up a list of lawless resolutes,\n\
For food and diet, to some enterprise\n\
That hath a stomach in't; which is no other--\n\
As it doth well appear unto our state--\n\
But to recover of us, by strong hand\n\
And terms compulsatory, those foresaid lands\n\
So by his father lost: and this, I take it,\n\
Is the main motive of our preparations,\n\
The source of this our watch and the chief head\n\
Of this post-haste and romage in the land..";
    
    // building message
    uint32_t dummy_message_size = strlen(dummy_message);
    msg->size = dummy_message_size;
    memcpy(msg->msg, dummy_message, dummy_message_size);

    // building block
    *((uint32_t*)buffer) = dummy_message_size;
    memcpy(buffer + 4, dummy_message, dummy_message_size);
}

void message_to_block_test() {
    uint32_t size = 2000;
    message_t *msg = (message_t*)malloc(size);
    char block[size], converted_block[size];
    memset(msg, 0, size);
    memset(block, 0, size);
    memset(converted_block, 0, size);

    init_message_block(msg, block);
    uint32_t actual_size = 1220;
    uint32_t block_size = *((uint32_t*)block);
    ASSERT_TEST(actual_size == msg->size + 4, "assert actual size and msg size are the same.");
    ASSERT_TEST(actual_size == block_size + 4, "assert actual size and block size are the same.");
    ASSERT_TEST(!memcmp(msg->msg, block + 4, actual_size - 4), "assert message are the same");
    message_to_block(msg, converted_block, actual_size);
    ASSERT_TEST(!memcmp(block, converted_block, actual_size), "assert blocks are the same");

    free(msg);
}

void block_to_message_test() {
    uint32_t size = 2000;
    message_t *msg = (message_t*)malloc(size);
    message_t *converted_msg = (message_t*)malloc(size);
    char block[size];
    memset(block, 0, size);
    memset(msg, 0, size);
    memset(converted_msg, 0, size);

    init_message_block(msg, block);
    uint32_t actual_size = 1220;
    uint32_t block_size = *((uint32_t*)block);
    ASSERT_TEST(actual_size == msg->size + 4, "assert actual size and msg size are the same.");
    ASSERT_TEST(actual_size == block_size + 4, "assert actual size and block size are the same.");
    ASSERT_TEST(!memcmp(msg->msg, block + 4, actual_size - 4), "assert message are the same");
    block_to_message(block, converted_msg, actual_size);
    ASSERT_TEST(!memcmp(msg, converted_msg, actual_size), "assert blocks are the same");

    free(msg);
}

int main() {
    RUN_TEST(message_to_block_test(), "test message encoded into message block.");
    RUN_TEST(block_to_message_test(), "test message decoded from message block."); 
}