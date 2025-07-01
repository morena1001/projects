const { SlashCommandBuilder, MessageFlags } = require ("discord.js");
const wait = require ('node:timers/promises').setTimeout;

module.exports = {
    cooldown: 5,
    data: new SlashCommandBuilder ()
        .setName ('ping')
        .setDescription ('Replies with Pong!'),
    async execute (interaction) {
        // await interaction.reply ({ content: 'Secret Pong!', flags: MessageFlags.Ephemeral });
        await interaction.reply ('Pong!');
        // await wait (2_000);
        // await interaction.editReply ('Pong again!');

        // await interaction.deferReply (/* { flags: MessageFlags.Ephemeral } */); 
        // await wait (4_000);
        // await interaction.editReply ('Pong!');

        // await interaction.reply ('Pong!');
        // await wait (500);
        // await interaction.followUp ('Pong again!' /* { content: 'Pong again!', flags: MessageFlags.Ephemeral } */);
        // await wait (1_000);
        // await interaction.deleteReply ();

        // await interaction.reply ({ content:'Pong!', withResponse: true });


    },
};
