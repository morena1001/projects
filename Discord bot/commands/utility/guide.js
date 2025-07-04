const { SlashCommandBuilder } = require ('discord.js');

module.exports = {
    cooldown: 5,
    data: new SlashCommandBuilder ()
        .setName ('guide')
        .setDescription ('Search discordjs.guide!')
        .addStringOption (option => 
            option.setName ('query')
                .setDescription ('Phrase to search for')
                .setAutocomplete (true))
        .addStringOption (option => 
            option.setName ('version')
                .setDescription ('Version to search in')
                .setAutocomplete (true)),
    async autocomplete (interaction) {
        const focusedOption = interaction.options.getFocused (true);
        let choices;

        if (focusedOption.name === 'query') {
            choices = ['Popular Topics: Threads', 'Sharding: Getting started', 'Library: Voice Connections', 'Interactions: Replying to slash commands', 'Popular Topics: Embed preview'];
        } 

        if (focusedOption.name === 'version') {
            choices = ['v9', 'v11', 'v12', 'v13', 'v14'];
        }

        // interaction.options.get('option').value

        // const focusedValue = interaction.options.getFocused ();
        // const choices = ['Popular Topics: Threads', 'Sharding: Getting started', 'Library: Voice Connections', 'Interactions: Replying to slash commands', 'Popular Topics: Embed preview'];
        const filtered = choices.filter (choice => choice.startsWith (focusedOption.value));
        await interaction.respond (
            filtered.map (choice => ({name: choice, value: choice})),
        );
    },         
    async execute (interaction) {
        
    }
};
