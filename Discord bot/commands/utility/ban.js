const { SlashCommandBuilder, PermissionFlagsBits, InteractionContextType } = require ('discord.js');

module.exports = {
    cooldown: 5,
    data: new SlashCommandBuilder ()
        .setName ('ban')
        .setDescription ('Select a member and ban them.')
        .addUserOption (option => 
            option.setName ('target')
                .setDescription ('The member to ban')
                .setRequired (true))
        .setDefaultMemberPermissions (PermissionFlagsBits.BanMembers)
        .setContexts (InteractionContextType.Guild),
    async execute (interaction) {
  
    }
};
