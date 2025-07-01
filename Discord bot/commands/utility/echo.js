const { SlashCommandBuilder, ChannelType } = require ('discord.js');

module.exports = {
    cooldown: 5,
    data: new SlashCommandBuilder ()
        .setName ('echo')
        .setDescription ('Replies with your input')
        .addStringOption (option => 
            option.setName ('input')
                .setDescription ('The input to echo back')
                // .setRequired (true)
                .setMaxLength (2_000))
        .addChannelOption (option =>
            option.setName ('channel')
            .setDescription ('The channel to echo into')
            .addChannelTypes (ChannelType.GuildText))
        .addBooleanOption (option =>
            option.setName ('ephemeral')
            .setDescription ('Whether or not the echo should be ephemeral'))
        .addBooleanOption(option =>
            option.setName('embed')
                .setDescription('Whether or not the echo should be embedded')),
    async execute (interaction) {
        const input = interaction.options.getString ('input') ?? "";
        const channel = interaction.options.getChannel ('channel');
        const ephemeral = interaction.options.getBoolean ('ephemeral') ?? true;
        const embed = interaction.options.getBoolean ('embed') ?? false;

        await interaction.reply (`${input}`);
    }
};
