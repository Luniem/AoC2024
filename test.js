const fs = require('fs');

const file = fs.readFileSync('input.json');
const data = JSON.parse(file);

const memberIds = Object.keys(data.members);

memberIds.forEach((memberId) => {
    const member = data.members[memberId];
    const completed = Object.keys(member.completion_day_level);

    if (completed.length > 0) {
        console.log('\n' + member.name);

        completed.forEach((day) => {
            const part1 = member.completion_day_level[day]['1'];
            const part2 = member.completion_day_level[day]['2'];

            if (part1) {
                console.log(`Day ${day} Part 1: ${new Date(part1.get_star_ts * 1000)} Part 2: ${new Date(part2.get_star_ts * 1000)}`);
            }
        });
    }
});
