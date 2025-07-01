const { SlashCommandBuilder, PermissionFlagsBits } = require ('discord.js');

module.exports = {
    cooldown: 5,
    data: new SlashCommandBuilder ()
        .setName ('kick')
        .setDescription ('Select a member and kick them.')
        .addUserOption (option => 
            option.setName ('target')
                .setDescription ('The member to kick')
                .setRequired (true))
        .setDefaultMemberPermissions (PermissionFlagsBits.KickMembers),
    async execute (interaction) {
  
    }
};
