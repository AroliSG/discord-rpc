#ifndef DISCORD_RPC_H
#define DISCORD_RPC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>

    /* Party Privacy Settings */
#define DISCORD_PARTY_PRIVATE 0
#define DISCORD_PARTY_PUBLIC 1

/* Join Request Reply */
#define DISCORD_REPLY_NO 0
#define DISCORD_REPLY_YES 1
#define DISCORD_REPLY_IGNORE 2

/* Discord User structure */
    typedef struct DiscordUser {
        const char* userId;
        const char* username;
        const char* discriminator;
        const char* avatar;
    } DiscordUser;

    /* Discord Rich Presence structure */
    typedef struct DiscordRichPresence {
        const char* state;          /* max 128 bytes */
        const char* details;        /* max 128 bytes */
        int64_t startTimestamp;
        int64_t endTimestamp;
        const char* largeImageKey;  /* max 32 bytes */
        const char* largeImageText; /* max 128 bytes */
        const char* smallImageKey;  /* max 32 bytes */
        const char* smallImageText; /* max 128 bytes */
        const char* partyId;        /* max 128 bytes */
        int partySize;
        int partyMax;
        const char* matchSecret;    /* max 128 bytes */
        const char* joinSecret;     /* max 128 bytes */
        const char* spectateSecret; /* max 128 bytes */
        int instance;               /* 0 or 1 */
    } DiscordRichPresence;

    /* Event Handlers for Discord */
    typedef struct DiscordEventHandlers {
        void (*ready)(const DiscordUser* connectedUser);
        void (*disconnected)(int errcode, const char* message);
        void (*errored)(int errcode, const char* message);
        void (*joinGame)(const char* joinSecret);
        void (*spectateGame)(const char* spectateSecret);
        void (*joinRequest)(const DiscordUser* request);
    } DiscordEventHandlers;

    /* Initialize the Discord RPC */
    void Discord_Initialize(const char* applicationId, DiscordEventHandlers* handlers, int autoRegister, const char* optionalSteamId);

    /* Shutdown the Discord RPC */
    void Discord_Shutdown(void);

    /* Clear the currently set Rich Presence */
    void Discord_ClearPresence(void);

    /* Update the current Rich Presence */
    void Discord_UpdatePresence(const DiscordRichPresence* presence);

    /* Run Discord callbacks (must be called frequently to handle events) */
    void Discord_RunCallbacks(void);

    /* Respond to a join request */
    void Discord_Respond(const char* userid, int reply);

#ifdef __cplusplus
}
#endif

#endif /* DISCORD_RPC_H */
