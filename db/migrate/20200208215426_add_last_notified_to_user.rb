class AddLastNotifiedToUser < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :last_notified, :timestamp
  end
end
