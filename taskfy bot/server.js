const express = require('express');
const app = express();
const port = 3000;
const mySecret = process.env['TOKEN']
const replies = ["Task??", "TASK", "... did someone say task?", "WHO CALLS THE TASKMAN", "Did I just hear the \"T\" word?", "Whomst has summoned the almighty one", "TASK TASK"]
const fs = require('fs')
const tucID = "447531834713047042";
const taskfyID = "333253699272966147";
const polybosID = "685554924372754510";

app.get('/', (req, res) => res.send('Hello World!'));

app.listen(port, () => console.log(`Example app listening at http://localhost:${port}`));

const { Client, Intents } = require('discord.js');

const client = new Client({ intents: [Intents.FLAGS.GUILDS, Intents.FLAGS.GUILD_MESSAGES] });

client.on('debug', console.log);

client.once('ready', () => {
	console.log('Ready!');
});

client.login(mySecret)

client.on("ready", () => {
    client.user.setActivity("Checking for tasks 24/7, also applying for task manager wish me luck");
});

client.on("messageCreate", async msg => {
    if ( msg.author.bot ) return;
    if ( msg.content.toLowerCase( ).includes("task") && msg.channel.name.includes("general") ) {
      msg.reply(replies[Math.floor(Math.random() * 7)])
    }

    if ( msg.content.toLowerCase( ).includes("!task") && !msg.channel.name.includes("general")) {
      if ( msg.content.toLowerCase( ).includes("help")) {
        msg.reply("Hey there. Simple list of commands:\n!task help -> well you just used that.\n!task taskmen -> shows the taskmen we have\n!task current <name> -> shows current task\n!task set <name> task -> sets current task that gets displayed\n...And that's it! For now anyway.")
      }
      if ( msg.content.toLowerCase( ).includes("taskmen")) {
        msg.reply("Current taskmen:\nTaskfy\nPolybos")
      }
      if ( msg.content.toLowerCase( ).includes("current")) {
        if ( msg.content.toLowerCase( ).includes("taskfy")) {
          fs.readFile('./data/Taskfy.txt', 'utf8', (err, data) => {
            if (err) {
              console.error(err);
            }
          msg.reply(data);
          });
        } else if ( msg.content.toLowerCase( ).includes("polybos")) {
          fs.readFile('./data/Polybos.txt', 'utf8', (err, data) => {
            if (err) {
              console.error(err);
            }
          msg.reply(data);
          });
        }
        else {
          msg.reply("Shit. You forgot to mention your desired taskman, or maybe you misspelled your taskman, try !task taskmen for a list of the chads we have")
        }
    }

    if ( msg.content.toLowerCase( ).includes("set")) {
      if ( msg.content.toLowerCase( ).includes("taskfy")) {
        if ( msg.author.id === taskfyID || msg.author.id === tucID ) {
          var task = msg.content.slice(10+7)
          fs.writeFile('./data/Taskfy.txt', task, err => {
            if (err) {
              console.error(err)
            }
          })
          msg.reply("Task set. New task: " + task)
        } else {
          msg.reply("Hey! You're not Taskfy, stop playing with me!")
        }
      }
      if ( msg.content.toLowerCase( ).includes("polybos")) {
        if ( msg.author.id === polybosID || msg.author.id === tucID ) {
          var task = msg.content.slice(10+8)
          fs.writeFile('./data/Polybos.txt', task, err => {
            if (err) {
              console.error(err)
            }
          })
          msg.reply("Task set. New task: " + task)
        } else {
          msg.reply("Hey! You're not Polybos, stop playing with me!")
        }
      }
    }
  }
});