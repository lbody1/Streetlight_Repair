# CS212 Data Structures - Project 77 Testing Documentation

## Test Categories & Detailed Scenarios

### Category 1: Normal Operations
- **TC-01: Asset Registration (Linked List & BST)**
  - **Input**: Add Pole ID `120`, Street: `Tahrir Square`, Type: `LED 150W`, Brightness: `100%`.
  - **Expected**: Node created in Linked List, ID indexed in BST root/branch, total count increments.
  - **Actual**: `[Success] Pole #120 registered in Inventory and indexed in BST.`
  - **Status**: PASS

- **TC-02: Outage Reporting (FIFO Queue Enqueue)**
  - **Input**: Report Pole ID `101`, Issue: `Flickering lamp`, Contact: `Eng. Tarek`, Priority: `High`.
  - **Expected**: BST finds ID, status in Linked List changes to "Faulty - Awaiting Repair", brightness becomes 0%, ticket enqueued to `RepairQueue`.
  - **Actual**: `[Success] Repair ticket generated and enqueued (FIFO) for technician dispatch.`
  - **Status**: PASS

- **TC-03: Technician Dispatch (FIFO Queue Dequeue -> LIFO Stack Push)**
  - **Input**: Option 9 (Dispatch Technician), Tech: `Eng. Hany`, Action: `Replaced LED driver chip`.
  - **Expected**: Dequeue front ticket, status restored to "Operational" (100% brightness), logged into `RepairStack`.
  - **Actual**: Pole status updated to Operational, repair logged in Stack.
  - **Status**: PASS

---

### Category 2: Boundary & Edge Cases
- **TC-04: Empty Queue Dequeue (Underflow Protection)**
  - **Input**: Select Option 9 when queue size is 0.
  - **Expected**: Gracefully informs user without crashing or null-pointer dereference.
  - **Actual**: `[Info] No broken lights in queue. All systems operating normally.`
  - **Status**: PASS

- **TC-05: Empty Stack Pop (Undo Underflow Protection)**
  - **Input**: Select Option 11 when no repairs have been completed.
  - **Expected**: Gracefully informs user that stack is empty.
  - **Actual**: `[Info] Repair history stack is empty. Nothing to undo.`
  - **Status**: PASS

- **TC-06: BST Deletion of Node with 2 Children**
  - **Input**: Delete Pole ID `105` (initial root with both left subtree 102 and right subtree 108).
  - **Expected**: Replaced by its inorder successor (`107`), left and right subtrees re-stitched correctly.
  - **Actual**: Clean removal, Inorder traversal remains sorted without missing nodes.
  - **Status**: PASS

---

### Category 3: Validation & Error Handling
- **TC-07: Duplicate ID Prevention**
  - **Input**: Add Pole ID `101` when `101` already exists.
  - **Expected**: BST search detects existing key; rejects insertion with clear message.
  - **Actual**: `[Error] Pole ID 101 already exists in system! Duplicate rejected.`
  - **Status**: PASS

- **TC-08: Non-numeric Menu Input**
  - **Input**: Enter `"hello"` or special characters at menu prompt.
  - **Expected**: `cin` failure cleared, input buffer purged, user reprompted.
  - **Actual**: `[Error] Invalid input. Please enter a valid number.` (no infinite loop).
  - **Status**: PASS

- **TC-09: Non-existent Pole Reporting**
  - **Input**: Report outage for Pole ID `999`.
  - **Expected**: BST returns false; no ticket created.
  - **Actual**: `[Error] Pole ID 999 does not exist in municipality records!`
  - **Status**: PASS

---

### Category 4: Multi-Structure Integration & Undo Reversal
- **TC-10: End-to-End Undo Quality Audit (LIFO Reversal)**
  - **Steps**:
    1. Report Pole `101` -> Enqueued.
    2. Dispatch Tech -> Dequeued -> Status becomes "Operational" -> Pushed to Stack.
    3. Supervisor Audits -> Triggers Undo (Option 11).
  - **Expected**:
    - Stack pops the repair log.
    - Pole `101` status reverts to `"Faulty - Repair Reverted"`.
    - Automatically re-enqueued into `RepairQueue` with `"High"` priority.
  - **Actual**: Pole successfully returned to Faulty and reappears in repair queue.
  - **Status**: PASS
