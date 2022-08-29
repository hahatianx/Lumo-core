#include <string.h>
#include <stdio.h>

#include "test.h"
#include "core.h"
#include "network/message.h"
#include "network/message_sender.h"


void test_send_message() {
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
    size_t message_len = strlen(dummy_message);
    message_task_t *task = new(message_task_t);
    message_t *msg = (message_t*)malloc(message_len + 4);
    msg->size = message_len;
    msg->msg = dummy_message;
    task->dst_addr = 0x7F000001;
    task->size = message_len + 4;
    task->msg = msg;

    send_message(task);
}
