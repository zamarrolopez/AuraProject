questLogButton = nil
questLineWindow = nil

function init()
    g_ui.importStyle('questlogwindow')
    g_ui.importStyle('questlinewindow')

    questLogButton = modules.game_mainpanel.addToggleButton('questLogButton', tr('Quest Log'),
                                                              '/images/options/button_questlog', function()
        g_game.requestQuestLog()
    end, false, 1000)

    connect(g_game, {
        onQuestLog = onGameQuestLog,
        onQuestLine = onGameQuestLine,
        onGameEnd = destroyWindows
    })

    Keybind.new("Windows", "Show/hide quest Log", "", "")
    Keybind.bind("Windows", "Show/hide quest Log", {
      {
        type = KEY_DOWN,
        callback =  function()
            g_game.requestQuestLog()
        end,
      }
    })
end

function terminate()
    disconnect(g_game, {
        onQuestLog = onGameQuestLog,
        onQuestLine = onGameQuestLine,
        onGameEnd = destroyWindows
    })

    destroyWindows()
    questLogButton:destroy()
    questLogButton = nil
    Keybind.delete("Windows", "Show/hide quest Log")
end

function destroyWindows()
    if questLogWindow then
        questLogWindow:destroy()
        questLogWindow = nil
    end

    if questLineWindow then
        questLineWindow:destroy()
        questLineWindow = nil
    end
end

function onGameQuestLog(quests)
    destroyWindows()

    questLogWindow = g_ui.createWidget('QuestLogWindow', rootWidget)
    local questList = questLogWindow:getChildById('questList')

    for i, questEntry in pairs(quests) do
        local id, name, completed = unpack(questEntry)

        local questLabel = g_ui.createWidget('QuestLabel', questList)
        questLabel:setOn(completed)
        questLabel:setText(name)
        questLabel.onDoubleClick = function()
            questLogWindow:hide()
            g_game.requestQuestLine(id)
        end
    end

    questLogWindow.onDestroy = function()
        questLogWindow = nil
    end

    questList:focusChild(questList:getFirstChild())
end

function onGameQuestLine(questId, questMissions)
    if questLogWindow then
        questLogWindow:hide()
    end
    if questLineWindow then
        questLineWindow:destroy()
        questLineWindow = nil
    end

    questLineWindow = g_ui.createWidget('QuestLineWindow', rootWidget)
    local missionList = questLineWindow:getChildById('missionList')
    local missionDescription = questLineWindow:getChildById('missionDescription')

    connect(missionList, {
        onChildFocusChange = function(self, focusedChild)
            if focusedChild == nil then
                return
            end
            missionDescription:setText(focusedChild.description)
        end
    })

    for i, questMission in pairs(questMissions) do
        local name, description, missionId = unpack(questMission)

        local missionLabel = g_ui.createWidget('MissionLabel')
        missionLabel:setText(name)
        missionLabel.description = description
        missionList:addChild(missionLabel)
    end

    questLineWindow.onDestroy = function()
        if questLogWindow then
            questLogWindow:show(true)
        end
        questLineWindow = nil
    end

    missionList:focusChild(missionList:getFirstChild())
end